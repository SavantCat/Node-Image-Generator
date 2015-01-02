var png = require('./index.js').png;
var jpg = require('./index.js').jpg;

var w = 10000;
var h = 10000;

var data = new Buffer(w*h*3);
data.fill(0);

var t=0;
/*
for(var i=0;i<h;i++){
    for(var j=0;j<w;j++){
        data.writeUInt8(i,t++);
        data.writeUInt8(j,t++);
        data.writeUInt8(100,t++); 
    }
}
*/

for(var i=0;i<h;i++){
    for(var j=0;j<w;j++){
        data.writeUInt8(Math.floor( Math.random() * 255 ),t++);
        data.writeUInt8(Math.floor( Math.random() * 255 ),t++);
        data.writeUInt8(Math.floor( Math.random() * 255 ),t++); 
    }
}

jpg.ToFile(w,h,3,50,'ToFile.jpg',data);
png.ToFile(w,h,'ToFile.png',data);