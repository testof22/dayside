<?
@session_start();
include ("inc.php");
if(isset($_POST["log"]) & $_POST["log"]!="")  {
	if (!check_log(deny_tags($_POST["log"]),deny_tags($_POST["pass"]))) {$err= "?err=неверный логин-пароль"; 
		
		
	}
	//header('location: http://'.$_SERVER['HTTP_HOST'].'/admin.php.$err'); //почему-то не заработал
	echo "<script>window.location.replace('http://".$_SERVER['HTTP_HOST']."/admin.php$err');</script>";
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"styles.css" rel="stylesheet" type="text/css" />

</head>

<body>




<? 


if(isset($_GET["err"])&&$_GET["err"]!="")  echo '<div id=messages>'.deny_tags($_GET["err"]).'</div>';
if(!isset($_SESSION["admin"]) || $_SESSION["admin"]=="") 
{
	?>
	<form name=adm_enter method=post>
	Логин: <input type="text" name="log" /> 
	Пароль: <input type="password" name="pass" />
	<input type="submit" value="Войти" />
	</form>
	<?	
	exit;
}

 	
	$link=connect_bd();
	//если выбрано поле для сорировки
	if(isset($_GET["order_by"]) & $_GET["order_by"]!="") $order_by = deny_tags($_GET["order_by"]); else $order_by="DateD";
	//order_by 
	//NameA - по имени по возрастанию
	//NameD - по имени по убыванию
	//StatusA - по статусу по возрастанию
	//StatusD - по статусу по убыванию	
	//EmailA - по почте по возрастанию
	//EmailD - по почте по убыванию		
	
	//если выбрана страница	
	if(isset($_GET["p"]) & $_GET["p"]!="") $page_num = deny_tags($_GET["p"]); else $page_num="";	
	


	
	//если были посланы данные для новой записи
	if(isset($_POST["edit_rec"]) & $_POST["edit_rec"]!="")  {
		
		//провеить и выдыть ошибки
		$array_edit_rec=check_data($_POST["uName_a"],$_POST["uEmail_a"],$_POST["uText_a"],$_POST["udate_a"],$_POST["id_a"]);
		//если нет ошибок, отправить в БД
		
		if ($array_edit_rec["errors_add"]=="") edit_bd_rec($link,$array_edit_rec);
		else echo '<div id=messages>'.$array_edit_rec["errors_edit"].'</div>';
		
	}
	 
?>
<h1>Все записи</h1>

<? 
	//собрать из БД все записи и вывести 
	show_all_enable_records_admin($link,$page_num,$order_by) ;
	

?>
</body>
</html>
