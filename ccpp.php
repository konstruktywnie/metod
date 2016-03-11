<?php
  $exclude = "_";
  $cppFile = ".cpp";
  $oFile = ".o";
  $mainexe = "main.exe";
  $cFlags = "";
  $lFlags = "";
  $compiler = "g++";
  $linker = "g++";
  $flagsFile = "!ccpp.txt";
  $objFolders = array();
  //$objFolders[] = ".";
  $stopOnMsg = " error: ";
  
  if( getCMLArgs( "-help", 1, true ) || getCMLArgs( "--help", 1, true ) || getCMLArgs( "/?", 1, true ) ) {
    echo "Easy compiling for c++ v2.1,  usage: ccpp [options]\n\n";
	echo "-e <exclude cpp files with this prefix> (default '$exclude')\n";
	echo "-cpp <cpp source files> (default '$cppFile')\n";
	echo "-obj <obj files> (default '$oFile')\n";
	echo "-exe <main output file> (default '$mainexe')\n";
	echo "-compiler <compiler> (default '$compiler')\n";
	echo "-linker <linker> (default '$linker')\n";
	echo "-stop (default '$stopOnMsg')\n";
	echo "-makefile <file with flags, first line for compiling second for linking, next for *$cppFile folders list> (default '$flagsFile')\n";
	
	exit( 0 );
  }
  
  $a = getCMLArgs( "-e", 1 );
  if( !empty( $a[0] ) ) $exclude = $a[0];
  $a = getCMLArgs( "-cpp", 1 );
  if( !empty( $a[0] ) ) $cppFile = $a[0];
  $a = getCMLArgs( "-obj", 1 );
  if( !empty( $a[0] ) ) $oFile = $a[0];
  $a = getCMLArgs( "-exe", 1 );
  if( !empty( $a[0] ) ) $mainexe = $a[0];
  $a = getCMLArgs( "-cflags", 1 );
  if( !empty( $a[0] ) ) $cFlags = $a[0];
  $a = getCMLArgs( "-lflags", 1 );
  if( !empty( $a[0] ) ) $lFlags = $a[0];
  $a = getCMLArgs( "-compiler", 1 );
  if( !empty( $a[0] ) ) $compiler = $a[0];
  $a = getCMLArgs( "-linker", 1 );
  if( !empty( $a[0] ) ) $linker = $a[0];
  $a = getCMLArgs( "-makefile", 1 );
  if( !empty( $a[0] ) ) $flagsFile = $a[0];
  $a = getCMLArgs( "-stop", 1 );
  if( !empty( $a[0] ) ) $stopOnMsg = $a[0];
  
  unset($a);
  
  $flagsFile = getcwd() . "\\" . $flagsFile;
  if( file_exists( $flagsFile ) ) {
    $cflagsFCont = file_get_contents( $flagsFile );
	$cflagsFCont = str_replace( "\r", "", $cflagsFCont );
	$flagsAr = explode( "\n", $cflagsFCont );
	
	if( strpos( $flagsAr[ 0 ], "#" ) !== false ) 
	  $cFlags = strstr( $flagsAr[ 0 ], "#", true ); 
	else $cFlags = $flagsAr[ 0 ];   
	
	if( strpos( $flagsAr[ 1 ], "#" ) !== false ) 
	  $lFlags = strstr( $flagsAr[ 1 ], "#", true ); 
	else $lFlags = $flagsAr[ 1 ];   
	
	$cFlags = trim( $cFlags ) . " ";
	$lFlags = trim( $lFlags ) . " ";
	$cflagsFSize = sizeof( $flagsAr );
	if( $cflagsFSize > 2 ) {
	  for( $i = 2; $i < $cflagsFSize; $i++ ) {
	    $oName = trim( $flagsAr[ $i ] );
		if( $oName != "" ) {
		  $objFolders[] = rtrim( $oName, DIRECTORY_SEPARATOR );
		 
		}
	  }
	}
	if( sizeof( $objFolders ) == 0 ) {
	  echo "Error: There are no folders in $flagsFile\n";
	  exit( 0 );
	}
    $allObj = "";
    $foldersNR = sizeof( $objFolders );
    for( $i = 0; $i < $foldersNR; $i++ )
      $allObj .= makeModules( $objFolders[ $i ] );

   // echo $allObj;
   // exit(0);
    if( !empty( $allObj ) ) {
      $linkCMD = "$linker $allObj -o $mainexe $lFlags";
      $out = shell_exec( "$linkCMD 2>&1" );
      echo "$linkCMD\n";
      echo $out;
    }
  } else {
    echo "Error: make file $flagsFile doesn't exist.\n";
	exit( 1 );
  }
  

function makeModules( $folder ) {
  global $stopOnMsg;
  global $cppFile;
  global $exclude;
  global $oFile;
  global $compiler;
  global $cFlags;
    
  $f = files_tree( $folder, false, false );
  $fs = sizeof( $f );
  for( $i = 0; $i < $fs; $i++ ) {
    //$f[ $i ] = trim( $f[ $i ] );
	$last_sep_pos = strrpos( $f[ $i ], DIRECTORY_SEPARATOR );
	$f[ $i ] = substr( $f[ $i ], $last_sep_pos + 1 );
    if( strtolower( substr( $f[ $i ], strlen( $f[ $i ] ) - strlen( $cppFile ) ) ) != $cppFile )
	  unset( $f[ $i ] );
	else 
	  if( substr( $f[ $i ], 0, strlen( $exclude ) ) == $exclude ) 
	    unset( $f[ $i ] );
  }
  $f = array_values( $f );

  $fs = sizeof( $f );
  $allModules = "";
  for( $i = 0; $i < $fs; $i++ ) {
    $cpp_format_pos = strrpos( $f[ $i ], $cppFile );
    $file = substr( $f[ $i ], 0, $cpp_format_pos );
	
    if( (file_exists( "$folder/$file$oFile" ) && (filemtime( "$folder/$file$cppFile" ) > filemtime( "$folder/$file$oFile" ))) || !file_exists( "$folder/$file$oFile" ) ) {  
	  $compileCMD = "$compiler $cFlags \"$folder/$file$cppFile\" -o \"$folder/$file$oFile\"";
	  $out = shell_exec( "$compileCMD 2>&1" );
	  echo "$compileCMD\n";
	  echo $out . "\n\n";
	
      if( strpos( $out, $stopOnMsg ) !== FALSE ) {
   	    exit( 1 );
  	  }	  
	}
	$allModules .= "\"$folder/$file$oFile\" ";
  }
  return $allModules;
}  
  
function files_tree( $dir, $d = false, $sd = true ) {   //$d - directories listings; $sd - subdirectories search
  $paths = '';
  $stack[] = $dir;
  while( $stack ) {
    $thisdir = array_pop( $stack );
    if( ($dircont = scandir( $thisdir )) !== FALSE ) {
      $c = sizeof( $dircont ); 
      for( $i = 0; $i < $c; $i++ ) {
	    if( $dircont[ $i ] != '.' && $dircont[ $i ] != '..' ) {
	      $current_file = $thisdir . DIRECTORY_SEPARATOR . "{$dircont[ $i ]}";
          if( is_file( $current_file ) )
		    $paths[] = $current_file;
          else {
		    if( $sd )
              $stack[] = $current_file;
		    if( $d )
			  $paths[] = $current_file;
		  }
        }
      }
    }
  }
  natsort( $paths );
  $paths = array_values( $paths );
  return $paths; 
}
function getCMLArgs( $switch, $nr, $foundSwitch = false ) {
  global $argv;
  global $argc;
  $fsw = false;
  $parameters = array();
  if( $argc > 1 && $nr > 0 )
    for( $i = 1; $i < $argc; $i++ ) {
      if( !strcmp( $argv[ $i ], $switch ) ) {
	    $fsw = true;
	    while( $nr-- > 0 && ++$i < $argc ) {
	      $parameters[] = $argv[ $i ];
		}
	  }
    }
  if( $foundSwitch == true && $fsw == true)	return true;
  if( $foundSwitch == true && $fsw == false) return false;
  return $parameters;
}
  
 
?>