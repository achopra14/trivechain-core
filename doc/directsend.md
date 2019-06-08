## DirectSend Technical Information

DirectSend has been integrated into the Core Daemon in two ways:
* "push" notifications (ZMQ and `-directsendnotify` cmd-line/config option);
* RPC commands.

#### ZMQ

When a "Transaction Lock" occurs the hash of the related transaction is broadcasted through ZMQ using both the `zmqpubrawtxlock` and `zmqpubhashtxlock` channels.

* `zmqpubrawtxlock`: publishes the raw transaction when locked via DirectSend
* `zmqpubhashtxlock`: publishes the transaction hash when locked via DirectSend

This mechanism has been integrated into Bitcore-Node-Trivechain which allows for notification to be broadcast through Insight API in one of two ways:
* WebSocket: [https://github.com/trivechain/insight-api-trivechain#web-socket-api](https://github.com/trivechain/insight-api-trivechain#web-socket-api)
* API: [https://github.com/trivechain/insight-api-trivechain#directsend-transactions](https://github.com/trivechain/insight-api-trivechain#directsend-transactions)

#### Command line option

When a wallet DirectSend transaction is successfully locked a shell command provided in this option is executed (`%s` in `<cmd>` is replaced by TxID):

```
-directsendnotify=<cmd>
```

#### RPC

Details pertaining to an observed "Transaction Lock" can also be retrieved through RPC, it’s important however to understand the underlying mechanism.

By default, the Trivechain Core daemon will launch using the following constant:

```
static const int DEFAULT_DIRECTSEND_DEPTH = 5;
```

This value can be overridden by passing the following argument to the Trivechain Core daemon:

```
-directsenddepth=<n>
```

The key thing to understand is that this value indicates the number of "confirmations" a successful Transaction Lock represents. When Wallet RPC commands which support `minconf` and `addlockconf` parameters (such as `listreceivedbyaddress`) are performed and `addlockconf` is `true`, then `directsenddepth` attribute is taken into account when returning information about the transaction. In this case the value in `confirmations` field you see through RPC is showing the number of `"Blockchain Confirmations" + "DirectSend Depth"` (assuming the funds were sent via DirectSend).

There is also a field named `instantlock` (that is present in commands such as `listsinceblock`). The value in this field indicates whether a given transaction is locked via DirectSend.

**Examples**

1. `listreceivedbyaddress 0 true`
   * DirectSend transaction just occurred:
        * confirmations: 5
   * DirectSend transaction received one confirmation from blockchain:
        * confirmations: 6
   * non-DirectSend transaction just occurred:
        * confirmations: 0
   * non-DirectSend transaction received one confirmation from blockchain:
        * confirmations: 1

2. `listreceivedbyaddress 0`
   * DirectSend transaction just occurred:
        * confirmations: 0
   * DirectSend transaction received one confirmation from blockchain:
        * confirmations: 1
   * non-DirectSend transaction just occurred:
        * confirmations: 0
   * non-DirectSend transaction received one confirmation from blockchain:
        * confirmations: 1

3. `listsinceblock`
    * DirectSend transaction just occurred:
        * confirmations: 0
        * instantlock: true
    * DirectSend transaction received one confirmation from blockchain:
        * confirmations: 1
        * instantlock: true
    * non-DirectSend transaction just occurred:
        * confirmations: 0
        * instantlock: false
    * non-DirectSend transaction received one confirmation from blockchain:
        * confirmations: 1
        * instantlock: false
