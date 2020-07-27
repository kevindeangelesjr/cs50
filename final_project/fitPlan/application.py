from flask import Flask, render_template, request, redirect, session
from flask_session import Session
import sqlite3
import os
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

### Application database
db = "fitPlan.db"

app = Flask(__name__)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def public():
    return render_template("public_home.html")


def error(message, code=400):
    """Render error page"""
    return render_template("error.html", message=message, code=code)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return error("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return error("must provide password", 403)

        # Query database for username
        username=request.form.get("username")
        conn = sqlite3.connect(db)
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=?", (username, ))
        rows=c.fetchall()
        conn.close()
        
        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0][2], request.form.get("password")):
            return error("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0][0]

        # Redirect user to home page
        return redirect("/home")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":

        ### Return register form
        return render_template("register.html")

    else:
        ### Return apology if any field was blank
        if not request.form.get("username"):
            return error("must provide username", 403)

        ### Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return error("must provide password", 403)

        ### Confirm passwords match
        if not (request.form.get("password") == request.form.get("confirmation")):
            return error("passwords must match", 403)

        ### Confirm username is free
        username=request.form.get("username")
        conn = sqlite3.connect(db)
        c = conn.cursor()
        rows = c.execute("SELECT * FROM users WHERE username=?", (username,))
        rows = c.fetchall()

        if len(rows) > 0:
            return error("that username is already taken", 403)

        else:
            ### hash password
            hash = generate_password_hash(request.form.get("password"))
                
        ### Insert into users table in DB
        c.execute("INSERT INTO users (username, hash) VALUES(?,?)", (username, hash))

        ### Create new tables to track the user's data

        conn.commit()
        conn.close()

        ### Redirect user to success page
        return redirect("/success")


@app.route("/success")
def success():
    return render_template("success.html")


@app.route("/home")
def home():
    return render_template("home.html")