var Tx = require('ethereumjs-tx');

module.exports = {
    __calcNumByte: function(num){
        var llTemp = 0;
        var i = 1;
        while(llTemp = num >> (i*8))
            i++;
        return i;
    },
    __web3RlpRemoveVRS: function(src){
        var rlpMsgBuffer = Buffer.from(src, 'hex');
        var lenByte = parseInt(rlpMsgBuffer[0]) - 0xF7;
        var len = parseInt('0x' + src.substr(2, 2 * lenByte));
        var newLenByte = this.__calcNumByte(len - 3);

        var rlp = Buffer.alloc(rlpMsgBuffer.length).fill(249);
        var t = (len - 3).toString(16).toUpperCase();
        if(t.length % 2 === 1) t = "0" + t;
        var hexLenBuffer = Buffer.from(t, 'hex');
        hexLenBuffer.copy(rlp, 1, 0, hexLenBuffer.length);
        rlpMsgBuffer.copy(rlp, 1+hexLenBuffer.length, lenByte+1, lenByte+1+len-3);
        var rlpLen = len-3+1+newLenByte;
        rlp = rlp.slice(0, rlpLen);

        return rlp.toString('hex').toUpperCase();
    },
    rlp: function(data, cb){
        var tx = new Tx(data);
        var rlpMsg = tx.serialize().toString('hex').toUpperCase();
        rlpMsg = this.__web3RlpRemoveVRS(rlpMsg);
        cb(0, rlpMsg);
    },
}