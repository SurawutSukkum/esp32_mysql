<?php
$host = "localhost";
$db = "u909844480_testMesh";
$user = "u909844480_testMesh";
$pass = "uXjNx9@I";

$conn = new mysqli($host, $user, $pass, $db);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$val = $_GET['node'];
$val1 = $_GET['data'];
$sql = "INSERT INTO mesh_data(node,data) VALUES ($val,$val1);";

if ($conn->query($sql) === TRUE) {
    echo "save OK2";
} else {
    echo "Error:" . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
