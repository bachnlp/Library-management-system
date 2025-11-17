<?php
$cookieName = "username";
setcookie($cookieName, "", time() - 3600);
echo "Cookie named 'username' has been deleted.";
?>
