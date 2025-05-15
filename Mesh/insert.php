<?php
$host = "localhost";
$db = "u909844480_testMesh";
$user = "u909844480_testMesh";
$pass = "uXjNx9@I";

$conn = new mysqli($host, $user, $pass, $db);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$node = $_POST['node'];
$data = $_POST['data'];

$stmt = $conn->prepare("INSERT INTO mesh_data (node, data) VALUES (?, ?)");
$stmt->bind_param("ss", $node, $data);

if ($stmt->execute()) {
    echo "Success";
} else {
    echo "Error: " . $stmt->error;
}

$stmt->close();
$conn->close();
?>
