<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        elseif (empty($_POST["email"]) || !filter_var($_POST["email"], FILTER_VALIDATE_EMAIL))
        {
            apologize("You must provide a valid mail adress.");
        }
        elseif ($_POST["password"] !== $_POST["confirmation"])
        {
            apologize("Password mismatch.");
        }
        elseif (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        elseif (!check_password($_POST["password"]))
        {
            apologize("Password must be at least 8 characters long, including 1 uppercase letter and 1 number.");
        }
        else
        {
            // register
            $register_query = query("INSERT INTO users (username, hash, cash, email) VALUES(?, ?, 10000.00, ?)", $_POST["username"], crypt($_POST["password"]), $_POST["email"] );
            
            // validation check
            if ($register_query === false) 
            {
                apologize("Username or email already used.");
            } 
            else
            {
                // get ID of new user
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                           
                // log user
                $_SESSION["id"] = $rows[0]["id"];
                redirect("/");
            }
        }
    }
?>
