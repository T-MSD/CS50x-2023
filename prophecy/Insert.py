from cs50 import SQL
import sys
import csv

db = SQL("sqlite:///new.db")

if len(sys.argv) != 2:
  sys.exit("Usage: python Insert.py students.csv")

with open(sys.argv[1], "r") as file:
  reader = csv.reader(file)
  # skip first csv file line
  next(reader)
  for row in reader:
      # Each dictionary
      dict = {"id": int(row[0]), "student": row[1], "house": row[2], "assignment": row[3]}
      db.execute("INSERT INTO students (student_name) VALUES (?)", dict["student"])
      db.execute("INSERT INTO houses (house, student) VALUES (?, ?)", dict["house"], dict["student"])
      db.execute("INSERT INTO assignments (assignment, student) VALUES (?, ?)", dict["assignment"], dict["student"])
