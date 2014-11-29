var png   = require('../png/build/Release/png');

process.stdin.resume();
process.stdin.setEncoding('utf8');

var data=[];

// 標準入力がくると発生するイベント
process.stdin.on('data', function (chunk) {
    chunk.trim().split('\n').forEach(function(line) {
        for(var i=0;i<20000;i++){
            data[i] = parseInt(Math.random()*255);
        }
        png.write_png(200,100,line,data);
    });
});
// EOFがくると発生するイベント
process.stdin.on('end', function (data) {
    
});