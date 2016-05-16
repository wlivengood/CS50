<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("funds_view.php", ["title" => "Add Funds"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["amount"]))
        {
            apologize("You must specify funds to be added");
        }
        
        $amount = $_POST["amount"];
        
        // check if amount is valid dollar amount
        if (preg_match('/^[0-9]+(?:\.[0-9]{0,2})?$/', $amount) == false)
        {
            apologize("Invalid dollar amount");
        }
        
        // check that amount doesn't exceed maximum
        if ($amount >= 1000000000000000)
        {
            apologize("Dollar amount exceeds maximum allowable");
        }

        else
        {
            // add cash to users table
            $query = CS50::query("UPDATE users SET cash = ? + ? WHERE id = ?", $_SESSION["cash"], $amount, $_SESSION["id"]);
            // update cash session superglobal
            $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            $_SESSION["cash"] = $rows[0]["cash"];
            // redirect to index
            redirect("/");
        }
    }

?>