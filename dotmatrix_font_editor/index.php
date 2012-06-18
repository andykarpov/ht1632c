<?php

    $widths = array(3,4,5,6,7,8);
    $heights = array(3,4,5,6,7,8,9,10,11,12,13,14,15,16);

    $width = (isset($_POST['width'])) ? (int) $_POST['width'] : 5;
    $height = (isset($_POST['height'])) ? (int) $_POST['height'] : 7;


    $chars = array_fill(32, 95, 0);
    $leds = (isset($_POST['led'])) ? $_POST['led'] : array();

    $src = '// dotmatrix font ' . $width . 'x' . $height . "\n";
    $src .= 'unsigned char PROGMEM ht1632c_font_' . $width . 'x' . $height . '[95][' . (($height > 8) ? $height : $width) . '] = {' . "\n";

    // pack rows
    if ($height > 8) {
        for ($c=32; $c<95+32; $c++) {
            $data = array();

            for ($y=0; $y<$height; $y++) {
                $bits = 'B';
                for ($x=0; $x<$width; $x++) {
                    $bits .= (!empty($leds[$c][$x][$y])) ? '1' : '0';
                }
                $bits .= str_repeat('0', 8-$width);
                $data[] = $bits;
            }
            $src .= '    { ' . join(', ', $data) .  ' }, // ' . chr($c) . "\n";
        }
    }
    // pack columns
    else {
        for ($c=32; $c<95+32; $c++) {
            $data = array();

            for ($x=0; $x<$width; $x++) {
                $bits = 'B';
                for ($y=0; $y<$height; $y++) {
                    $bits .= (!empty($leds[$c][$x][$y])) ? '1' : '0';
                }
                $bits .= str_repeat('0', 8-$height);
                $data[] = $bits;
            }
            $src .= '    { ' . join(', ', $data) .  ' }, // ' . chr($c) . "\n";
        }
    }

    $src .= "};\n";
?>
<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
    <meta name="viewport" content="width=device-width,initial-scale=1">
    <title>Dot matrix font editor 1.0</title>
    <script type="text/javascript" src="js/jquery-1.6.2.js"></script>
    <script type="text/javascript">
        $(document).ready(function(){
            $('.led').click(function(){
               if ($(this).hasClass('on')) {
                   $(this).removeClass('on').addClass('off');
               } else {
                   $(this).removeClass('off').addClass('on');
               }
               var state = $(this).hasClass('on') ? true : false;
               $(this).find('input').eq(0).val((state) ? '1' : '0');
            });
        });
    </script>
    <style type="text/css">

        body {
            padding: 20px;
            background: #333;
            color: #fff;
        }

        * {
            font-family: Arial, Helvetica, sans-serif;
        }

        ul {
            display: block;
            position: relative;
            padding: 0;
            margin: 0;
            list-style-type: none;
        }

        ul li {
            display: block;
            position: relative;
            float: left;
            margin: 0 5px 5px 0;
            padding: 0;
            background: #333;
        }

        ul li h3 {
            color: #fff;
            font-size: 12px;
            text-align: center;
            padding: 0;
            margin: 0 0 2px 0;
        }

        ul li div.row {
            display: block;
            position: relative;
            padding: 0;
            margin: 0;
        }

        ul li.div.row.row_3 {
            width: 48px;
        }
        ul li.div.row.row_4 {
            width: 64px;
        }
        ul li.div.row.row_5 {
            width: 80px;
        }
        ul li.div.row.row_6 {
            width: 96px;
        }
        ul li.div.row.row_7 {
            width: 112px;
        }
        ul li.div.row.row_8 {
            width: 128px;
        }

        ul li div.led {
            display: block;
            position: relative;
            float: left;
            width: 16px;
            height: 16px;
            padding: 0;
            margin: 0;
            background-position: top left;
            background-repeat: no-repeat;
            cursor: pointer;
        }

        ul li div.led.on {
            background-image: url(i/led-on.gif);
        }

        ul li div.led.off {
            background-image: url(i/led-off.gif);
        }

        div.spacer {
            display: block;
            position: relative;
            height: 20px;
        }

            /* http://webdesignerwall.com/tutorials/css3-gradient-buttons */
        .button {
            display: inline-block;
            outline: none;
            cursor: pointer;
            text-align: center;
            text-decoration: none;
            font: 12px/100% Verdana, Tahoma, Arial, Helvetica, sans-serif;
            padding: .5em 1.5em .55em;
            text-shadow: 0 1px 1px rgba(0,0,0,.3);
            -webkit-border-radius: .5em;
            -moz-border-radius: .5em;
            border-radius: .5em;
            -webkit-box-shadow: 0 1px 2px rgba(0,0,0,.2);
            -moz-box-shadow: 0 1px 2px rgba(0,0,0,.2);
            box-shadow: 0 1px 2px rgba(0,0,0,.2);
        }
        .button:hover {
            text-decoration: none;
        }
        .button:active {
            position: relative;
            top: 1px;
        }

            /* black */
        .black {
            color: #d7d7d7;
            border: solid 1px #333;
            background: #333;
            background: -webkit-gradient(linear, left top, left bottom, from(#666), to(#000));
            background: -moz-linear-gradient(top,  #666,  #000);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#666666', endColorstr='#000000');
        }
        .black:hover {
            background: #000;
            background: -webkit-gradient(linear, left top, left bottom, from(#444), to(#000));
            background: -moz-linear-gradient(top,  #444,  #000);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#444444', endColorstr='#000000');
        }
        .black:active {
            color: #666;
            background: -webkit-gradient(linear, left top, left bottom, from(#000), to(#444));
            background: -moz-linear-gradient(top,  #000,  #444);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#000000', endColorstr='#666666');
        }

            /* orange */
        .orange {
            color: #fef4e9;
            border: solid 1px #da7c0c;
            background: #f78d1d;
            background: -webkit-gradient(linear, left top, left bottom, from(#faa51a), to(#f47a20));
            background: -moz-linear-gradient(top,  #faa51a,  #f47a20);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#faa51a', endColorstr='#f47a20');
        }
        .orange:hover {
            background: #f47c20;
            background: -webkit-gradient(linear, left top, left bottom, from(#f88e11), to(#f06015));
            background: -moz-linear-gradient(top,  #f88e11,  #f06015);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#f88e11', endColorstr='#f06015');
        }
        .orange:active {
            color: #fcd3a5;
            background: -webkit-gradient(linear, left top, left bottom, from(#f47a20), to(#faa51a));
            background: -moz-linear-gradient(top,  #f47a20,  #faa51a);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#f47a20', endColorstr='#faa51a');
        }

            /* gray */
        .gray {
            color: #e9e9e9;
            border: solid 1px #555;
            background: #6e6e6e;
            background: -webkit-gradient(linear, left top, left bottom, from(#888), to(#575757));
            background: -moz-linear-gradient(top,  #888,  #575757);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#888888', endColorstr='#575757');
        }
        .gray:hover {
            background: #616161;
            background: -webkit-gradient(linear, left top, left bottom, from(#757575), to(#4b4b4b));
            background: -moz-linear-gradient(top,  #757575,  #4b4b4b);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#757575', endColorstr='#4b4b4b');
        }
        .gray:active {
            color: #afafaf;
            background: -webkit-gradient(linear, left top, left bottom, from(#575757), to(#888));
            background: -moz-linear-gradient(top,  #575757,  #888);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#575757', endColorstr='#888888');
        }

            /* green */
        .green {
            color: #e8f0de;
            border: solid 1px #538312;
            background: #64991e;
            background: -webkit-gradient(linear, left top, left bottom, from(#7db72f), to(#4e7d0e));
            background: -moz-linear-gradient(top,  #7db72f,  #4e7d0e);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#7db72f', endColorstr='#4e7d0e');
        }
        .green:hover {
            background: #538018;
            background: -webkit-gradient(linear, left top, left bottom, from(#6b9d28), to(#436b0c));
            background: -moz-linear-gradient(top,  #6b9d28,  #436b0c);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#6b9d28', endColorstr='#436b0c');
        }
        .green:active {
            color: #a9c08c;
            background: -webkit-gradient(linear, left top, left bottom, from(#4e7d0e), to(#7db72f));
            background: -moz-linear-gradient(top,  #4e7d0e,  #7db72f);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#4e7d0e', endColorstr='#7db72f');
        }

            /* white */
        .white {
            color: #606060;
            border: solid 1px #b7b7b7;
            background: #fff;
            background: -webkit-gradient(linear, left top, left bottom, from(#fff), to(#ededed));
            background: -moz-linear-gradient(top,  #fff,  #ededed);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#ffffff', endColorstr='#ededed');
        }
        .white:hover {
            background: #ededed;
            background: -webkit-gradient(linear, left top, left bottom, from(#fff), to(#dcdcdc));
            background: -moz-linear-gradient(top,  #fff,  #dcdcdc);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#ffffff', endColorstr='#dcdcdc');
        }
        .white:active {
            color: #999;
            background: -webkit-gradient(linear, left top, left bottom, from(#ededed), to(#fff));
            background: -moz-linear-gradient(top,  #ededed,  #fff);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#ededed', endColorstr='#ffffff');
        }

            /* red */
        .red {
            color: #faddde;
            border: solid 1px #980c10;
            background: #d81b21;
            background: -webkit-gradient(linear, left top, left bottom, from(#ed1c24), to(#aa1317));
            background: -moz-linear-gradient(top,  #ed1c24,  #aa1317);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#ed1c24', endColorstr='#aa1317');
        }
        .red:hover {
            background: #b61318;
            background: -webkit-gradient(linear, left top, left bottom, from(#c9151b), to(#a11115));
            background: -moz-linear-gradient(top,  #c9151b,  #a11115);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#c9151b', endColorstr='#a11115');
        }
        .red:active {
            color: #de898c;
            background: -webkit-gradient(linear, left top, left bottom, from(#aa1317), to(#ed1c24));
            background: -moz-linear-gradient(top,  #aa1317,  #ed1c24);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#aa1317', endColorstr='#ed1c24');
        }

            /* blue */
        .blue {
            color: #d9eef7;
            border: solid 1px #0076a3;
            background: #0095cd;
            background: -webkit-gradient(linear, left top, left bottom, from(#00adee), to(#0078a5));
            background: -moz-linear-gradient(top,  #00adee,  #0078a5);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#00adee', endColorstr='#0078a5');
        }
        .blue:hover {
            background: #007ead;
            background: -webkit-gradient(linear, left top, left bottom, from(#0095cc), to(#00678e));
            background: -moz-linear-gradient(top,  #0095cc,  #00678e);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#0095cc', endColorstr='#00678e');
        }
        .blue:active {
            color: #80bed6;
            background: -webkit-gradient(linear, left top, left bottom, from(#0078a5), to(#00adee));
            background: -moz-linear-gradient(top,  #0078a5,  #00adee);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#0078a5', endColorstr='#00adee');
        }

            /* pink */
        .pink {
            color: #feeef5;
            border: solid 1px #d2729e;
            background: #f895c2;
            background: -webkit-gradient(linear, left top, left bottom, from(#feb1d3), to(#f171ab));
            background: -moz-linear-gradient(top,  #feb1d3,  #f171ab);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#feb1d3', endColorstr='#f171ab');
        }
        .pink:hover {
            background: #d57ea5;
            background: -webkit-gradient(linear, left top, left bottom, from(#f4aacb), to(#e86ca4));
            background: -moz-linear-gradient(top,  #f4aacb,  #e86ca4);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#f4aacb', endColorstr='#e86ca4');
        }
        .pink:active {
            color: #f3c3d9;
            background: -webkit-gradient(linear, left top, left bottom, from(#f171ab), to(#feb1d3));
            background: -moz-linear-gradient(top,  #f171ab,  #feb1d3);
            filter:  progid:DXImageTransform.Microsoft.gradient(startColorstr='#f171ab', endColorstr='#feb1d3');
        }

        .hidden { display: none !important; visibility: hidden; }
        .visuallyhidden { border: 0; clip: rect(0 0 0 0); height: 1px; margin: -1px; overflow: hidden; padding: 0; position: absolute; width: 1px; }
        .visuallyhidden.focusable:active, .visuallyhidden.focusable:focus { clip: auto; height: auto; margin: 0; overflow: visible; position: static; width: auto; }
        .invisible { visibility: hidden; }
        .clearfix:before, .clearfix:after { content: ""; display: table; }
        .clearfix:after { clear: both; }
        .clearfix { zoom: 1; }

        form div.field {
            display: block;
            position: relative;
            width: 600px;
            height: auto;
            margin-bottom: 20px;
        }

        form div.field label {
            display: block;
            position: relative;
            margin-right: 10px;
            margin-bottom: 5px;
            font-weight: bold;
            font-size: 13px;
        }

        form div.field input.text, form div.field select {
            display: block;
            position: relative;
            width: 300px;
            height: auto;
            font-size: 14px;
            line-height: 22px;
            padding: 5px 10px;
        }

        form textarea {
            width: 800px;
            height: 300px;
            color: #fff;
            background: #333;
        }

    </style>
</head>
<body>

    <h1>Dot matrix font editor</h1>

    <p>Please specify your new font dimensions in the form below, then click &laquo;Update&raquo;</p>
    
    <form method="post" action="index.php">

        <div class="field">
            <label for="field-width">Font width:</label>
            <select class="text" name="width" id="field-width">
                <?php foreach($widths as $w): ?>
                <option value="<?php echo $w?>" <?php echo ($w == $width) ? 'selected="selected"' : ''?>><?php echo $w?></option>
                <?php endforeach; ?>
            </select>
            <div class="clearfix"></div>
        </div>

        <div class="field">
            <label for="field-height">Font height:</label>
            <select class="text" name="height" id="field-height">
                <?php foreach($heights as $h): ?>
                <option value="<?php echo $h?>" <?php echo ($h == $height) ? 'selected="selected"' : ''?>><?php echo $h?></option>
                <?php endforeach; ?>
            </select>
            <div class="clearfix"></div>
        </div>

        <input type="submit" class="button green" value="Update"/>

        <!-- <p>Or please choose and upload a BDF font file below:</p>
        <div class="field">
            <label for="field-file">BDF font:</label>
            <input type="file" id="field-file" name="file" class="text"/>
            <div class="clearfix"></div>
        </div>

        <input type="submit" class="button blue" value="Upload"/>
        -->

        <div class="spacer"></div>

        <h2>Font (<?php echo $width?> x <?php echo $height?>) editor:</h2>
        <ul>
            <?php foreach($chars as $code => $char): ?>
            <li>
                <h3><?php echo htmlspecialchars(chr($code)). '&nbsp;'?></h3>
                <?php for ($y=0; $y < $height; $y++): ?>
                <div class="row row_<?php echo $width?>" id="char_<?php echo (string)$code?>_row_<?php echo (string)$y?>">
                    <?php for($x=0; $x < $width; $x++): ?>
                        <div id="led_<?php echo (string)$code?>_row_<?php echo (string)$x?>_<?php echo (string)$y?>" class="led <?php echo (!empty($leds[$code][$x][$y])) ? 'on' : 'off' ?>">
                            <input type="hidden" name="led[<?php echo (string)$code?>][<?php echo (string)$x?>][<?php echo (string)$y?>]" value="<?php echo (!empty($leds[$code][$x][$y])) ? '1' : '0' ?>"/>
                        </div>
                    <?php endfor; ?>
                </div>
                <?php endfor; ?>
            </li>
            <?php endforeach; ?>
        </ul>

        <div class="clearfix"></div>
        <div class="spacer"></div>

        <input type="submit" class="button red" value="Show me the code"/>

        <h2><label for="field-code">Your C header file for this font:</label></h2>
        <textarea cols="80" rows="20" id="field-code" name="code"><?php echo $src?></textarea>
    </form>

</body>
</html>