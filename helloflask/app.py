from flask import Flask, render_template, request

app = Flask(__name__)

colors = ["red", "blue"]

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
      return render_template("index.html")
    else:
       print("Form submitted!")
       color = request.form.get("color")
       if color not in colors:
          return render_template("failed.html")
       return render_template("color.html", color=color)