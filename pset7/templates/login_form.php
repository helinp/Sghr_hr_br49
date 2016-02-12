<main class="col-md-12">
    <form action="login.php" method="post">
        <fieldset>
            <div class="form-group">
                <input autofocus class="form-control" name="username" placeholder="username" type="text"/>
            </div>
            <div class="form-group">
                <input class="form-control" name="password" placeholder="password" type="password"/>
                <br /><small><a href="forgot.php">Forgot password?</a></small>
            </div>
            <div class="form-group">
                <button type="submit" class="btn btn-default">Login</button>
            </div>
        </fieldset>
    </form>
    <div>
        or <a href="register.php">Register</a>.
    </div>
</main>
