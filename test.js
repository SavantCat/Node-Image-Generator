var png = require('./index.js').png;

var w = 500;
var h = 500;

var data = new Buffer(w*h*3);
data.fill(0);

for(var i=0;i<h;i++){
    for(var j=w*3*i;j<w*3+w*3*i;){
        data.writeUInt8(255,j++);
        data.writeUInt8(255,j++);
        data.writeUInt8(255,j++); 
    }
}


png.ToFile(w,h,'ToFile.png',data);

var buf = png.ToBuffer(w,h,data);
console.log(buf);

var fs = require('fs');
fs.writeFile('ToBuffer.png', buf , function (err) {
    console.log('complete!');
});   



