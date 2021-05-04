
<?php

$servername = "localhost:3307";
$username = "root";
$password = "";
$dbname = "monitor";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
$sql = "SELECT * FROM esp32 ORDER by No DESC LIMIT 20";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {

    }
	echo "</table>";
} else {
    echo "0 results";
}
$conn->close();

?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <title>ทดสอบระบบ</title>

    <!-- Bootstrap -->
    <!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7" crossorigin="anonymous">

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>
  <body>
    <h1>บันทึกสภาพแวดล้อมปัจจุบัน</h1>
			
		<table class="table" id="esp32">
			<thead>
				<tr>
					<th>ลำดับ</th>
					<th>อุณหภูมิ(องศาเซลเซียส)</th>
                                        <th>ความชื้น (%)</th>
                                        <th>เวลา</th>
                                        <th>วันที่</th>
				</tr>
			</thead>
			<tbody>
				<?php
					foreach($result as $result_tb){
						echo"<tr>";
							echo "<td>".$result_tb['No']."</td>";
							echo "<td>".$result_tb['Temp']."*C</td>";
							echo "<td>".$result_tb['Humi']."%</td>";
                                                        echo "<td>".$result_tb['Time']."</td>";
							echo "<td>".$result_tb['Date']."</td>";
						echo"</tr>";
					}
				?>
			
			</tbody>
		</table>

		
	<script src="http://code.jquery.com/jquery-1.12.0.min.js"></script>
	<script src="https://code.highcharts.com/highcharts.js"></script>
	<script src="https://code.highcharts.com/modules/data.js"></script>
	<script src="https://code.highcharts.com/modules/exporting.js"></script>	
  </body>
</html>
