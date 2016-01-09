var modbus = require('jsmodbus');

// create a modbus client
var client = modbus.createTCPClient(8085, '127.0.0.1', function (err) {
    if (err) {
        console.log(err);
        process.exit(0);
    }
});

client.readHoldingRegister(0, 2, function(resp, err){
    console.log(err, resp.register);
});
