<?
   include ("inc.php");
   $link=connect_bd();
  //если были посланы данные для новой записи
  if(isset($_POST["add_new_rec"]) & $_POST["add_new_rec"]!="")  {
	  
	  //провеить и выдыть ошибки
	  $array_new_rec=check_data($_POST["uName"],$_POST["uEmail"],$_POST["uText"],$_POST["udate"]);
	  //если нет ошибок, отправить в БД
  
	  if ($array_new_rec["errors_add"]=="") {
		  add_bd_new_rec($link,$array_new_rec);
	  }
	  else $err= "?err=".$array_new_rec["errors_add"];
	  
	  echo "<script>window.location.replace('http://".$_SERVER['HTTP_HOST']."/$err');</script>";
  }
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Документ без названия</title>


</head>

<body>
<? 

	//print_r($_POST);
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
	
if(isset($_GET["err"])&&$_GET["err"]!="") echo '<div id=messages>'.deny_tags($_GET["err"]).'</div>';



	 
?>
<h1>Все записи</h1>

<? 
	//собрать из БД все записи и вывести 
 show_all_enable_records($link,$page_num,$order_by) ;
	

 //вывести форму для новой записи
 show_form_new_rec($link);
?>

</body>
</html>
