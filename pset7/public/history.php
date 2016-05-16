<?php

    // configuration
    require("../includes/config.php"); 
    
    // query history
    $rows = CS50::query("SELECT transaction, time_stamp, symbol, shares, price FROM history WHERE user_id = ?", $_SESSION["id"]);
    // create array of arrays(key-value pairs) as positions to pass to history_view via render
    $positions = [];
    foreach ($rows as $row)
    {
       $positions[] = [
           "transaction" => $row["transaction"],
           "time_stamp" => $row["time_stamp"],
           "symbol" => $row["symbol"],
           "shares" => $row["shares"],
           "price" => $row["price"]
           ];
    }
    
    render("history_view.php", ["positions" => $positions, "title" => "History"]);
?>
