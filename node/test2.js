var png   = require('../png/build/Release/png');
var util = require('util');
process.stdin.resume();
process.stdin.setEncoding('utf8');

var w = 500;
var h = 200;

// 標準入力がくると発生するイベント
process.stdin.on('data', function (chunk) {
    chunk.trim().split('\n').forEach(function(line) {
        var data = new Array(w*h*3);
        
        for(var i=0;i<h*w*3;i++){
            data[i] = 0;
        }
        
        for(var i=0;i<h;i++){
            for(var j=w*3*i;j<w*3+w*3*i;){
                //console.log(j);
                data[j++]=0;
                data[j++]=255;
                data[j++]=0; 
            }
        }
        /*
        for(var i=0;i<h*w*3;i++){

            console.log(i +"," +data[i]);
        }
        */
        png.write_png_rgb(w,h,line,data);
    });
});
// EOFがくると発生するイベント
process.stdin.on('end', function (data) {
    
});