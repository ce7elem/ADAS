
fs = require('fs');

const wstream = fs.createWriteStream('/tmp/myfifo')
setInterval( ()=> {
	  console.log(`message ${process.hrtime()[0]}`)
	  wstream.write(`message ${process.hrtime()[0]}\n`)
}, 1000)
