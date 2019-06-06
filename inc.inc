<?


 /*вывод формы для новой записи */
function  show_form_new_rec($link){
	$udate=time();//Время создания записи
	$udate_format=date("d-m-Y H:i", $udate);//форматированное время создания
 ?>
	<h1>Оставить новую задачу</h1>
     
    <!-- форма ввода -->
     <form name=enter_rec action="/" method="post" >
     <table width="100%" border="1" cellspacing="0" cellpadding="0">
        <tr><td>Имя:</td><td><input  name="uName" type="text" size="80" value=""/></td></tr>
        <tr><td>Дата:</td><td><?=$udate_format;	?><input name="udate" type="hidden" value="<?=$udate?>" /></td></tr>
        <tr><td>Email:</td><td><input  name="uEmail" type="text" size="80" value=""/></td></tr>
        <tr><td>Текст:</td><td><textarea  name="uText" cols="90" rows="5"></textarea> </td></tr>  
         
     </table>
     
    <input name="add_new_rec" type="submit" value="Отправить" />
    
    <input name="" type="reset" value="Очистить поля" />
    </form>
    <!-- end форма ввода -->
<?
}


/////////////////////////////////////////////////////////////////////////////////////////////
/*Подключение к БД*/
function connect_bd(){
	//print "****";
	$link = mysqli_connect("mysql.zzz.com.ua", "testof22", "2598pRscg2a", "testof22");
	

	if (mysqli_connect_errno()) {
		printf("Не удалось подключиться: %s\n", mysqli_connect_error());
		exit();
	}
	
	return $link;	
	
}
/////////////////////////////////////////////////////////////////////////////////////////////
/*Выбор и вывод всех доступных записей с соответвующей сортировкой*/
function select_all_rec($link, $order_by,$page_num=""){
$order_str = "rec_id";
	
	switch($order_by){
		case NameA: $order_str=" ORDER BY rec_uName ASC"; break;
		case NameD: $order_str=" ORDER BY rec_uName DESC"; break;
		case StatusA: $order_str=" ORDER BY rec_status ASC"; break;
		case StatusD: $order_str=" ORDER BY rec_status DESC"; break;
		case EmailA: $order_str=" ORDER BY rec_uEmail ASC"; break;
		case EmailD: $order_str=" ORDER BY rec_uEmail DESC"; break;
	}
	
	 if ($page_num=="" ) $limit=" LIMIT 0,3"; 
	 else {
		 $limit=" LIMIT ".(($page_num-1)*3).", 3";
	 }
	//rec_id rec_uName 	rec_uDate 	rec_uEmail 	rec_text 	rec_status 
	$query="SELECT * FROM rec_tbl   $order_str $limit";
	//print $query;
	$result = mysqli_query ($link, $query);	
	if ( isset($result) && mysqli_num_rows($result)!=0) {
			
			while ($one_row=mysqli_fetch_array($result, MYSQLI_ASSOC)) {
				$records[$one_row["rec_id"]]["rec_id"]= $one_row["rec_id"];	
				$records[$one_row["rec_id"]]["rec_uName"]= $one_row["rec_uName"];	
				$records[$one_row["rec_id"]]["rec_uDate"]= date("d-m-Y H:i", $one_row["rec_uDate"]);
				$records[$one_row["rec_id"]]["rec_uEmail"]= $one_row["rec_uEmail"];
				$records[$one_row["rec_id"]]["rec_text"]= $one_row["rec_text"];  
				$records[$one_row["rec_id"]]["rec_status"]= $one_row["rec_status"];
			
			
			}
			mysqli_free_result($result);
					
			
			
			empty($finfo);
			empty($query);
			

			
			return $records;
	}	

}
/////////////////////////////////////////////////////////////////////////////////////////////
/*вывод записей в страницу */
function show_all_enable_records ($link, $page_num="",$order_by=""){
	$array_records=select_all_rec($link,$order_by,$page_num);
	if(count($array_records)==0) {echo "<b>Записи отсутствуют</b>"; return false;}
?>
<!-- Все записи-->

<p>Имя 
      <a href="/?order_by=NameA">up</a>
      <a href="/?order_by=NameD">dwn</a>
</p>
<p>Статус
      <a href="/?order_by=StatusA">up</a>
      <a href="/?order_by=StatusD">dwn</a>
</p>
<p>e-mail
      <a href="/?order_by=EmailA">up</a>
      <a href="/?order_by=EmailA">dwn</a>    
</p>
-------------------------------------------------------------------
 <?	
 
	foreach ($array_records as $id => $array_rec){
		if($array_rec["rec_status"]==1) $changed="Выполенно"; 
		else $changed="Не выполненно";
?>
	<!-- вывод записи id#<?=$id?> -->
<p><?=$array_rec["rec_uName"]?> | <?=$array_rec["rec_uDate"]?>| <?=$array_rec["rec_uEmail"]?> </p>
<p><?=$array_rec["rec_text"]?></p>
<p><?=$changed?></p>
<p>*****************************************************</p>

 <!-- end вывод записи id#<?=$id?> -->

<!-- end Все записи-->
 
 
<?
    }
	//вывод страниц
	//всего записей в таблице (для расчета страниц)
	$query="SELECT rec_id FROM rec_tbl"; 
	$result = mysqli_query ($link, $query);	
	$count_all_rec=mysqli_num_rows($result);
			
	$summ_pages=floor($count_all_rec/3)+1;
	
	for ($i=1; $i<=$summ_pages;$i++) {
		if($i==$page_num) $i_str="<b>".$i."</b>"; else $i_str=$i;
		echo "<a href='/?p=".$i."&order_by=".$order_by."'>".$i_str."</a> ";
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/*вывод записей в страницу админ */
function show_all_enable_records_admin ($link, $page_num="",$order_by=""){
	$array_records=select_all_rec($link,$order_by,$page_num);
	if(count($array_records)==0) {echo "<b>Записи отсутствуют</b>"; return false;}
?>
<!-- Все записи-->

<p>Имя 
      <a href="/?order_by=NameA">up</a>
      <a href="/?order_by=NameD">dwn</a>
</p>
<p>Статус
      <a href="/?order_by=StatusA">up</a>
      <a href="/?order_by=StatusD">dwn</a>
</p>
<p>e-mail
      <a href="/?order_by=EmailA">up</a>
      <a href="/?order_by=EmailA">dwn</a>    
</p>
-------------------------------------------------------------------
 <?	
	foreach ($array_records as $id => $array_rec){
		if($array_rec["rec_status"]==1) { $changed="Выполенно"; $ched="checked";}
		else { $changed="Не выполненно"; $ched="";}
?>
	<!-- вывод записи id#<?=$id?> -->
    <!-- форма ввода -->
     <form name=edit_rec action="" method="post" >
     <table width="100%" border="1" cellspacing="0" cellpadding="0">
        <tr><td>Имя:</td><td><input  name="uName_a" type="text" size="80" value="<?=$array_rec["rec_uName"]?>"/></td></tr>
        <tr><td>Дата:</td><td><input name="udate_a" type="text" value="<?=$array_rec["rec_uDate"]?>" /></td></tr>
        <tr><td>Email:</td><td><input  name="uEmail_a" type="text" size="80" value="<?=$array_rec["rec_uEmail"]?> "/></td></tr>
        <tr><td>Текст:</td><td><textarea  name="uText_a" cols="90" rows="5"><?=$array_rec["rec_text"]?></textarea> </td></tr> 
        <input  name="id_a" type="hidden" value="<?=$id?>"/> 
        <tr><td>Проверка:</td><td><input name="chbox" type="checkbox" value="checked" <?=$ched?> > </td></tr>   
     </table>
     
    <input name="edit_rec" type="submit" value="Отправить" />
    
    <input name="" type="reset" value="Очистить поля" />
    </form>
    <!-- end форма ввода -->

<p>*****************************************************</p>

 <!-- end вывод записи id#<?=$id?> -->

<!-- end Все записи-->
 
 
<?
    }
	//вывод страниц
			//всего записей в таблице (для расчета страниц)
			$query="SELECT rec_id FROM rec_tbl"; 
			$result = mysqli_query ($link, $query);	
			$count_all_rec=mysqli_num_rows($result);
			
	$summ_pages=floor($count_all_rec/3)+1;
	
	for ($i=1; $i<=$summ_pages;$i++) {
		
		if($i==$page_num) $i_str="<b>".$i."</b>"; else $i_str=$i;
		echo "<a href='?p=".$i."&order_by=".$order_by."'>".$i_str."</a> ";
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
/*Очистка строки от тегов и спецсимволов*/
function deny_tags($str){
	$str=trim($str);
	$str=strip_tags($str);
	return $str;	
}



/////////////////////////////////////////////////////////////////////////////////////////////
/*Проверка введенных данных*/
function check_data($uName,$uEmail,$uText,$udate,$id="" ){
	
	$array_new_data["errors_add"]	="";	
		
	$array_new_data["uName"]= $uName;
	if($array_new_data["uName"]=="") $array_new_data["errors_add"]= "Не заполнено поле \"Имя\". ";
	
	$array_new_data["uEmail"]= deny_tags($uEmail);	
	if($array_new_data["uEmail"]=="" || filter_var($array_new_data["uEmail"], FILTER_VALIDATE_EMAIL) =="")
	           $array_new_data["errors_add"].= "Не правильно заполнено поле \"Email\"";
			   
	$array_new_data["uText"]=deny_tags($uText);
	$array_new_data["udate"]=$udate;
	$array_new_data["id"]=$id;
	return $array_new_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//добаление записи в БД
function add_bd_new_rec($link,$array_new_data){
	
			$query="INSERT INTO `rec_tbl` (`rec_id`, `rec_uName`, `rec_uDate`, `rec_uEmail`, `rec_text`, `rec_status`) 
			VALUES (NULL, '".$array_new_data["uName"]."', 
			              '".$array_new_data["udate"]."', 
						  '".$array_new_data["uEmail"]."', 
						  '".$array_new_data["uText"]."', 
						  '0')"; 
			//print $query;
			$result = mysqli_query ($link, $query);	
                    		
}
/////////////////////////////////////////////////////////////////////////////////////////////
//редактирование записи
function edit_bd_rec ($link,$array_edit_data){
	if($_POST["chbox"] =="checked") $array_edit_data["rec_status"]=1; else $array_edit_data["rec_status"]=0;
			$query="UPDATE `rec_tbl` 
			SET `rec_uName` = '".$array_edit_data["uName"]."' ,
			`rec_uEmail` = '".$array_edit_data["uEmail"]."' ,
			`rec_text` = '".$array_edit_data["uText"]."' ,
			`rec_status` = '".$array_edit_data["rec_status"]."' 
			WHERE `rec_tbl`.`rec_id` =".$array_edit_data["id"]." ";
			
			
			$result = mysqli_query ($link, $query);	
}
/////////////////////////////////////////////////////////////////////////////////////////////
function check_log ($log, $pass){
	
	if($log=="admin" && $pass=="123") {
		
		$_SESSION["admin"]="OK";	
		return true;
	}
	return false;
}
?>
