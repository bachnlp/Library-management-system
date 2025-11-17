<?php
if (checkAccess('delete_user')) echo '<a href="delete.php">Delete User</a>';
if (checkAccess('edit_user')) echo '<a href="edit.php">Edit User</a>';
if (checkAccess('view_user')) echo '<a href="list.php">View Users</a>';
?>
