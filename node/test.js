var png   = require('../png/build/Release/png');

process.stdin.resume();
process.stdin.setEncoding('utf8');

var data=[];

var fs = require('fs');
fs.readFile('./250000test.txt', function (err, text) {
    console.log('text file!');
    console.log(text);
    console.log('error!?');
    console.log(err);
    
    png.write_png_rgb(500,500,"test.png",text);
    
    process.exit();
});
