# console-utility
钱包客户端的一些实用方法

安装
-----
`npm install git+ssh://http://luchenqun:fendoubuxi@192.168.9.66/Juzix-ethereum/console-utility.git#develop`   
如果是写到package.json里面，以git协议这么写：
`'console-utility':git+ssh://http://luchenqun:fendoubuxi@192.168.9.66/Juzix-ethereum/console-utility.git#develop`

说明
-----
* 大部分文件方法提供同步以及异步的调用。建议使用均使用异步调用。异步调用大部分回调函数均以`function(err, data1, data2, ...){}`返回，第一个参数是错误返回代码，0为正常，其他为异常。

使用
-----
如果你在Node.js环境下面使用，先引入：
`var util = require("console-utility");`   
一个调用示例如下：
```JavaScript
var rawTx = {
    gasPrice: 21000000000,
    gasLimit: 9999999999,
    value: 0,
    nonce: 0x00,
    to: "0x1176fd5dc45001002eb2b893e5ef7c4884756407",
    data: "0xb1498e290000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000018a7b226964223a227371732d31222c226e616d65223a22535153222c22706172656e744964223a2261646d696e222c226465736372697074696f6e223a22626c6f636b636861696e20706c6174222c22636f6d6d6f6e4e616d65223a225465737431222c2273746174654e616d65223a224744222c22636f756e7472794e616d65223a22434e222c22656d61696c223a227465737431403132362e636f6d222c2274797065223a312c22656e6f64654c697374223a5b7b227075626b6579223a2230783331643137376235623261626133396531633330366331623333383334643234356538356435373763343332366237363162373334323365636139303063616536366638376432333430633135356634303238353832303663396533656566653830376363323433616636323864623138363064393965373132653535343862222c226970223a223139322e3136382e31302e3335222c22706f7274223a223130303031227d5d2c22726f6c6549644c697374223a5b5d2c2266696c6549644c697374223a5b5d7d000000000000"
}
var util = require("console-utility");
util.rlp(rawTx, function (err, rlpMsg) {
    console.log(err, rlpMsg);
})
```   

测试
-----
执行`npm run test`即可。里面有一些调用接口的示例，也可进行参考。

方法说明 
--------------------------
### **`rlp(rawTx, callback)`** 
通过交易数据，返回交易数据的RLP编码。  
* `rawTx` Object 交易数据。
* `callback`: Function 回调函数。回调获得两个参数 (err, rlpMsg)，err为错误返回码。0为无错误，其他有错误。rlpMsg为转换后的rlp编码。



