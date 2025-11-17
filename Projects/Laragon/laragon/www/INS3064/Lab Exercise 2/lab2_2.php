<?php
function hasPermission($user_id, $permission) {
    global $user_roles, $roles;
    $user_role = $user_roles[$user_id] ?? 'guest';
    return in_array($permission, $roles[$user_role]);
}
?>
