<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match.");
        }
        
        // check if username already exists
        $rows = CS50::query("SELECT * FROM users WHERE username = ?", $_POST["username"]);
        if (count($rows) != 0)
        {
            apologize("Username already exists.");
        }
        
        // else insert username and password into database
        else
        {
            $query = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
            
            // error check
            if ($query === false)
            {
                apologize("An error occurred.");
            }
            
            // store user id and cash amount in SESSION superglobal
            else
            {
                $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
                $_SESSION["id"] = $id;
                $rows = CS50::query("SELECT cash FROM users WHERE username = ?", $_POST["username"]);
                $cash = $rows[0]["cash"];
                $_SESSION["cash"] = $cash;
                redirect("/");
            }
        }
    }

?>