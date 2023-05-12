import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)


# pk_79d2469803314fde872b6efb209c0603


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user ID
    user_id = session["user_id"]
    # Get user stock holdings
    user_stocks = db.execute("SELECT * FROM holdings WHERE user_id = ?", user_id)
    # Get user cash
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = user_cash[0]["cash"]

    # All stocks value
    value = 0
    for stock in user_stocks:
        # Add to value all holdings on that stock
        value += stock["stock_value"]
        # Get stock price and add a dict field for price
        this_stock = lookup(stock["symbol"])
        stock["price"] = this_stock["price"]

    return render_template("index.html", stocks=user_stocks, cash=cash, value=value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("Must provide a symbol", 400)

        symbol = request.form.get("symbol")
        buying_stock = lookup(symbol.upper())

        # Ensure stock exists
        if not buying_stock:
            return apology("Invalid symbol", 400)

        # Ensure number of shares was submitted
        if not request.form.get("shares"):
            return apology("Must provide a number of shares", 400)

        shares = request.form.get("shares")

        # Ensure that the number of shares is a positive integer
        if not shares.isdigit() or int(shares) < 1:
            return apology("The number of shares must be a positive integer", 400)

        # Get user id
        user_id = session["user_id"]
        shares_price = float(shares) * buying_stock["price"]
        # Get user cash
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]
        cash_left = user_cash - shares_price

        # Ensure that the user has enough money
        if cash_left < 0:
            return apology("Not enough money", 400)

        # Update users cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_left, user_id)

        # Get transaction time
        date = datetime.now()

        # Get all user stocks
        holding_stocks = db.execute("SELECT * FROM holdings WHERE user_id = ?", user_id)
        # Control variable
        added = 0
        user_shares = 0
        for stock in holding_stocks:
            if stock["symbol"] == symbol:
                # Update user shares of that symbol
                db.execute("UPDATE holdings SET shares = ? WHERE user_id = ? AND symbol = ?",
                           stock["shares"] + int(shares), user_id, symbol.upper())
                user_shares = stock["shares"] + int(shares)
                added = 1
                break

        # Add transaction to the history table
        db.execute("INSERT INTO history (user_id, symbol, shares, price, date, type) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, symbol.upper(), shares, buying_stock["price"], date, "buy")

        # If it is the first time the user is buying this stock
        if added == 0:
            # Add new stock to the holdings table
            db.execute("INSERT INTO holdings (user_id, symbol, shares) VALUES (?, ?, ?)", user_id, symbol.upper(), int(shares))
            user_shares = int(shares)

        # Update total value of the stock
        db.execute("UPDATE holdings SET stock_value = ? WHERE user_id = ? AND symbol = ?",
                   user_shares * buying_stock["price"], user_id, symbol.upper())

        # Get all user stocks to display on the webpage
        user_stocks = db.execute("SELECT * FROM holdings WHERE user_id = ?", user_id)

        # Total holdimgs value
        value = 0
        for stock in user_stocks:
            value += stock["stock_value"]
            this_stock = lookup(stock["symbol"])
            stock["price"] = this_stock["price"]

        return render_template("index.html", stocks=user_stocks, cash=cash_left, value=value)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get user id
    user_id = session["user_id"]
    # Get all user trasactions
    transactions = db.execute("SELECT * FROM history WHERE user_id = ?", user_id)

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide a symbol", 400)

        symbol = request.form.get("symbol")
        stock = lookup(symbol.upper())

        # Ensure stock exists
        if not stock:
            return apology("Invalid symbol", 400)

        return render_template("quoted.html", stock=stock)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("Must provide password", 400)

        # Ensure passowrd confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("Must confirm password", 400)

        # Ensure passowrd and confirmation are the same
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("Password and confirmation must be the same", 400)

        # Create a password hash
        password_hash = generate_password_hash(request.form.get("password"))
        username = request.form.get("username")

        # Get all usernames
        usernames = db.execute("SELECT username FROM users")

        # Check if the username already exists
        for name in usernames:
            if name["username"] == username:
                return apology("Username already exists", 400)

        # Create new user in the data base
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash)

        return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Get user id
    user_id = session["user_id"]
    # Get user holdings
    user_stocks = db.execute("SELECT * FROM holdings WHERE user_id = ?", user_id)

    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("Must select a stock", 400)

        # Ensure the number of shares was submitted
        if not request.form.get("shares"):
            return apology("Must provide a number of shares", 400)

        symbol = request.form.get("symbol")
        shares_to_sell = request.form.get("shares")

        # Ensure that it is a positive integer
        if not shares_to_sell.isdigit() or int(shares_to_sell) < 1:
            return apology("The number of shares must be a positive integer")

        actual_shares = 0
        stock = lookup(symbol)
        for this_stock in user_stocks:
            # Check if it is the right stock
            if this_stock["symbol"] == symbol:
                # Ensure the user has enough shares to sell
                if int(this_stock["shares"]) < int(shares_to_sell):
                    return apology("Not enough shares")
                # Check if the user is selling all shares
                if int(this_stock["shares"]) - int(shares_to_sell) == 0:
                    # If it is remove that stock from the holdings table
                    db.execute("DELETE FROM holdings WHERE user_id = ? AND symbol = ?", user_id, symbol)
                    break
                # Update the number of holding shares
                actual_shares = int(this_stock["shares"]) - int(shares_to_sell)
                db.execute("UPDATE holdings SET shares = ?, stock_value = ? WHERE user_id = ? AND symbol = ?",
                           actual_shares, stock["price"] * actual_shares, user_id, symbol)
                break

        date = datetime.now()

        # Add transaction to the history table
        db.execute("INSERT INTO history (user_id, symbol, shares, price, date, type) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, symbol, -int(shares_to_sell), stock["price"], date, "sell")

        # Get the updated stocks
        updated_user_stocks = db.execute("SELECT * FROM holdings WHERE user_id = ?", user_id)

        # Get user cash
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = user_cash[0]["cash"]
        cash += stock["price"] * int(shares_to_sell)

        # Update users cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

        # All stocks value
        value = 0
        for stock in updated_user_stocks:
            # Add to value all holdings on that stock
            value += stock["stock_value"]
            # Get stock price and add a dict field for price
            this_stock = lookup(stock["symbol"])
            stock["price"] = this_stock["price"]

        return render_template("index.html", stocks=updated_user_stocks, cash=cash, value=value)

    else:
        return render_template("sell.html", stocks=user_stocks)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("Insert your password", 400)

        # Get user id
        user_id = session["user_id"]
        password = request.form.get("password")
        # Get password hash
        user_hash = db.execute("SELECT hash FROM users WHERE id = ?", user_id)

        # Check if the password is right
        if not check_password_hash(user_hash[0]["hash"], password):
            return apology("Wrong password", 400)

        # Ensure new password was submitted
        if not request.form.get("new_password"):
            return apology("Insert new password", 400)

        # Ensure password confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("Confirm new password", 400)

        # Check if the new password is the old one
        if request.form.get("new_password") == password:
            return apology("New password can't be the the old one", 400)

        confirm_password = request.form.get("confirmation")
        new_password = request.form.get("new_password")

        # Check if the new password and the confirmation are the same
        if not confirm_password == new_password:
            return apology("Passwords don't match")

        # Generate new password hash
        password_hash = generate_password_hash(new_password)

        # Update user hash
        db.execute("UPDATE   users SET hash = ? WHERE id = ?", password_hash, user_id)

        # Forget any user_id
        session.clear()

        # Redirect user to login form
        return redirect("/")

    else:
        return render_template("change_password.html")
