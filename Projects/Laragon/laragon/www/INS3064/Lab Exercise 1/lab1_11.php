<?php
session_save_path('D:/Projects/Laragon/laragon/custom/'); session_start();
$sessionTimeout = 1800; 
if (isset ($_SESSION['LAST_ACTIVITY'])) 
{
$lastActivity = $_SESSION['LAST_ACTIVITY']; $currentTime = time(); $timeSinceLastActivity = $currentTime - $lastActivity;
if ($timeSinceLastActivity > $sessionTimeout)
{
session_unset(); session_destroy(); echo "Session expired. Please log in again.";
} else {
$_SESSION['LAST_ACTIVITY'] = $currentTime; echo "Session active.";
}
} else {
$_SESSION['LAST_ACTIVITY'] = time(); echo "Session started.";} ?>
