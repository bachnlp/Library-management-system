<?php
$cookieName = "visited";
if (isset($_COOKIE[$cookieName])) {
echo "Welcome back! You've visited before.";
} else {
echo "Welcome! This is your first visit.";
}
?>

