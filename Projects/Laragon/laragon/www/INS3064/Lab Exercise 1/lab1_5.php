<?php
session_save_path('D:/Projects/Laragon/laragon/custom/');

session_start();
if (isset($_SESSION["userid"])) {
$userid = ["userid"];
echo "Value of session variable userid: ". $userid;
} else {
echo "Session variable 'userid' not found.";
}
