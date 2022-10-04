<?php
// dichiaro le variabili che ricevo da arduino
$temperatura = $_GET['temperatura'];
$umidita = $_GET['umidita'];
$pressione = $_GET['pressione'];
$luminosita = $_GET['luminosita'];
$pioggia = $_GET['pioggia'];
$neve = $_GET['neve'];
$monossido = $_GET['monossido'];
$vento = $_GET['vento'];
$rugiada = $_GET['rugiada'];

$timpe_stamp = strtotime("now");
$date = date('d m Y',$time_stamp);

// effettuo la connessione al mysqli
$host = "www.miosito.it";
$username = "nomeutente";
$database = "my_database";
$password = "";
$tabella = "mytabella";

$link = mysqli_connect($host, $username, $password);

if (!$link) {
    die('non connesso : ' . mysql_error());
}

// effettuo la connessione al database mysql
$db_selected = mysqli_select_db($link, $database);
if (!$db_selected) {
    die ('Non è possibile connettersi al database : ' . mysql_error());
}
else{
echo "DataBase Connesso... ";

}

$query = "INSERT INTO my_stazionemeteoarduino.meteo (temperatura, umidita, pressione, luminosita, pioggia, neve, monossido, vento, rugiada, time_stamp) VALUES ($temperatura, $umidita, $pressione, $luminosita, $pioggia, $neve, $monossido, $vento, $rugiada, CURRENT_TIMESTAMP)";
if (mysql_query($query))
echo "Inserimento corretto";
else
echo "Errore durante l'inserimento";

?>
