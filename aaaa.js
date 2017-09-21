// CryptoPebble.js
// Ver.1.0 - 2017.9.20

// ---------------------------------------------------
// 設定
// ---------------------------------------------------

// モード ( \n は改行)

var $modes = [
  {
    "subtitle": "XRP MODE",
    "body": "C: $cc_jpy_xrp\nC: $cc_btc_xrp\nB: $bt_btc_xrp\nP: $polo_btc_xrp"
  },
  {
    "subtitle": "BTC MODE",
    "body": "C: $cc_jpy_btc\nC: $cc_usd_btc\nB: $bt_usdt_btc\nP: $polo_usdt_btc"
  },
  {
    "subtitle": "ETH MODE",
    "body": "C: $cc_jpy_eth\nC: $cc_btc_eth\nB: $bt_btc_eth\nP: $polo_btc_eth"
  },
  {
    "subtitle": "Zaif MODE",
    "body": "Zaif: $zf_jpy_zaif\nXEM: $zf_jpy_xem\nMona: $zf_jpy_mona\nPePe: $zf_jpy_pepecash"
  },
  {
    "subtitle": "bitFlyer MODE",
    "body": "BTCJPY: $bf_btc_jpy\nFXBTCJPY: $bf_fx_btc_jpy\nBCHBTC: $bf_bch_btc\nETHBTC: $bf_eth_btc"
  },
  {
    "subtitle": "Bitfinex USD",
    "body": "BTC: $bfx_usd_btc\nETH: $bfx_usd_eth\nETC: $bfx_usd_etc\nXRP: $bfx_usd_xrp"
  },
  {
    "subtitle": "CMC Mode",
    "body": "PINK: $cmc_jpy_pinkcoin\n420G: $cmc_jpy_ganjacoin\nTIT: $cmc_jpy_titcoin\nDOGE: $cmc_jpy_dogecoin"
  },
  {
    "subtitle": "bitbank.cc",
    "body": "MONA: $bb_jpy_mona\nXRP: $bb_jpy_xrp\nBTC: $bb_jpy_btc\nBCC: $bb_jpy_bcc"
  },
  {
    "subtitle": "OKCoin MODE",
    "body": "BTC: $ok_usd_btc\nLTC: $ok_usd_ltc\nETH: $ok_usd_eth\nETC: $ok_usd_etc"
  },
  {
    "subtitle": "XRP: $cc_jpy_xrp\nXEM: $cc_jpy_xem",
    "body": "BTC: $cc_jpy_btc\nBCH: $cc_jpy_bch"
  },
]

// 更新間隔 (秒)

var $interval = 20;

// デフォルトの表示モード (0〜2）
// 0: デフォルトモード 例) 0.00004713
// 1: satoshiモード    例) 4713s
// 2: 指数モード       例) 4.713e-5

var $currentDecimalMode = 0;

// CoinMarketCapのサポート (true / false)

var $supportCoinMarketCap = true;

// ---------------------------------------------------
// 以下処理部
// ---------------------------------------------------

var $currentMode = 0;
var $poloJSON = {};
var $status = {};

function floatFormat(number, n) {
  var _pow = Math.pow(10, n);
  return Math.round(number * _pow) / _pow;
}

function zeroFill(num, fill) {
  var padd = "0000000000";
  return (padd + num).slice(-fill);
}

function timeText() {
  var now = new Date();
  var n = {
    month: zeroFill(now.getMonth() + 1, 2),
    date: zeroFill(now.getDate(), 2),
    hours: zeroFill(now.getHours(), 2),
    minutes: zeroFill(now.getMinutes(), 2)
  }
  return util2.format("$month/$date - $hours:$minutes", n);
}

function updatePoloJSON() {
  try {
    ajax({
      url: 'https://poloniex.com/public?command=returnTicker',
      type: 'json',
      async: false
    }, function (data) {
      $poloJSON = data;
    });
  } catch (e) {
    console.log(e);
    simply.body(e);
  }
}

try {
  ajax({
    url: 'https://coincheck.com/api/rate/all',
    type: 'json',
    async: false
  }, function (data) {
    for (var i in data["jpy"]) {
      // 丸め桁を調整する場合は、digitsを適宜設定する -> 現状CCのJPYと各取引所のUSD(T)ペアのみfloatFormatを使用
      $status["cc_jpy_" + i] = {
        "value": "xxxx",
        "digits": 2
      }
    }
    for (var i in data["btc"]) {
      $status["cc_btc_" + i] = {
        "value": "xxxx",
        "digits": 2
      }
    }
    $status["cc_usd_btc"] = {
        "value": "xxxx",
        "digits": 2
      }
  });
  ajax({
    url: 'https://api.zaif.jp/api/1/currency_pairs/all',
    type:'json',
    async: false
  }, function(data) {
    for (var i = 0; i < data.length; i++) {
      $status["zf_" + data[i]["currency_pair"].split("_").reverse().join("_")] = {
        "value": "xxxx",
        "digits": 2
      }
    }
  });
  ajax({
    url: 'https://api.bitflyer.jp/v1/markets',
    type: 'json',
    async: false
  }, function (data) {
    for (var i = 0; i < data.length; i++) {
      $status["bf_" + data[i]["product_code"].toLowerCase()] = {
        "value": "xxxx",
        "digits": 2
      };
    }
  });
  ajax({
    url: 'https://poloniex.com/public?command=returnTicker',
    type: 'json',
    async: false
  }, function (data) {
    for (var i in data) {
      $status["polo_" + i.toLowerCase()] = {
        "value": "xxxx",
        "digits": 2
      };
    }
  });
  ajax({
    url: 'https://bittrex.com/api/v1.1/public/getmarkets',
    type: 'json',
    async: false
  }, function (data) {
    for (var i = 0; i < data["result"].length; i++) {
      $status["bt_" + data["result"][i]["MarketName"].replace("-", "_").toLowerCase()] = {
        "value": "xxxx",
        "digits": 2
      };
    }
  });
  ajax({
    url: 'https://api.bitfinex.com/v1/symbols',
    type: 'json',
    async: false
  }, function (data) {
    for (var i = 0; i < data.length; i++) {
      $status["bfx_" + data[i].replace(/(btc|eth|usd)$/, ",$1").split(",").reverse().join("_")] = {
        "value": "xxxx",
        "digits": 2
      };
    }
  });
  if ($supportCoinMarketCap) {
    ajax({
      url: 'http://crypto.hitoriblog.com/coinmarketcap_markets.php',
      type: 'json',
      async: false
    }, function (data) {
      for (var i = 0; i < data.length; i++) {
        $status[data[i]] = {
          "value": "xxxx",
          "digits": 2
        };
      }
    });    
  }
  // bitbank.cc
  var data = ["btc_jpy", "xrp_jpy", "ltc_btc", "eth_btc", "mona_jpy", "mona_btc", "bcc_jpy", "bcc_btc"];
  for (var i = 0; i < data.length; i++) {
    $status["bb_" + data[i].split("_").reverse().join("_")] = {
        "value": "xxxx",
        "digits": 2
    }
  }
  // ok coin
  var data = ["btc_usd", "ltc_usd", "eth_usd", "etc_usd", "bcc_usd"];
  for (var i = 0; i < data.length; i++) {
    $status["ok_" + data[i].split("_").reverse().join("_")] = {
        "value": "xxxx",
        "digits": 2
    }
  }
} catch (e) {
  console.log(e);
  simply.body(e);
}

function toSatoshi(f, digits) {
  return floatFormat(f * 100000000, digits) + "s";
}

function cc_update(pair, digits) {
  try {
    ajax({
      url: 'https://coincheck.com/api/rate/' + pair.replace("cc_", "").split("_").reverse().join("_"),
      type: 'json',
      async: false
    }, function (data) {
      if (pair.match(/^cc_jpy/) || pair.match(/^cc_usd/)) {
        $status[pair]["value"] = floatFormat(data["rate"], digits);
      } else {
        switch ($currentDecimalMode) {
          case 0:
            $status[pair]["value"] = data["rate"];
            break;
          case 1:
            $status[pair]["value"] = toSatoshi(parseFloat(data["rate"]), digits);
            break;
          case 2:
            $status[pair]["value"] = parseFloat(data["rate"]).toExponential();
            break;
        }
      }
    });
  } catch (e) {
    console.log(e);
    simply.body(e);
  }
}

function zf_update(pair, digits) {
  try {
    ajax({
      url: 'https://api.zaif.jp/api/1/last_price/' + pair.replace("zf_", "").split("_").reverse().join("_"),
      type: 'json',
      async: false
    }, function (data) {
      if (pair.match(/^zf_jpy/)) {
        $status[pair]["value"] = floatFormat(data["last_price"], digits);
      } else {
        switch ($currentDecimalMode) {
          case 0:
            $status[pair]["value"] = data["last_price"];
            break;
          case 1:
            $status[pair]["value"] = toSatoshi(parseFloat(data["last_price"]), digits);
            break;
          case 2:
            $status[pair]["value"] = parseFloat(data["last_price"]).toExponential();
            break;
        }
      }
    });
  } catch (e) {
    console.log(e);
    simply.body(e);
  }
}

function bf_update(pair, digits){
  try {
    ajax({
      url: 'https://api.bitflyer.jp/v1/ticker?product_code=' + pair.replace("bf_", "").toUpperCase(),
      type:'json',
      async: false
      }, function(data) {
      if (pair.match(/jpy/)) {
        $status[pair]["value"] = floatFormat(data["best_bid"], digits);  
      } else {
        switch ($currentDecimalMode) {
          case 0:
            $status[pair]["value"] = data["best_bid"];
            break;
          case 1:
            $status[pair]["value"] = toSatoshi(parseFloat(data["best_bid"]), digits);
            break;
          case 2:
            $status[pair]["value"] = parseFloat(data["best_bid"]).toExponential();
            break;
        }
        /*
        if ($toExponential) {
          $status[pair]["value"] = parseFloat(data["best_bid"]).toExponential();
        } else {
          $status[pair]["value"] = data["best_bid"];
        }
        */
      }
    });
  } catch (e) {
    console.log(e);
    simply.body(e);
  }
}

function polo_update(pair, digits) {
  if ($poloJSON[pair.replace("polo_", "").toUpperCase()] !== undefined) {
    if (pair.match(/^polo_usdt/)) {
      $status[pair]["value"] = floatFormat($poloJSON[pair.replace("polo_", "").toUpperCase()]["last"], digits);
    } else {
      switch ($currentDecimalMode) {
        case 0:
          $status[pair]["value"] = $poloJSON[pair.replace("polo_", "").toUpperCase()]["last"];
          break;
        case 1:
          $status[pair]["value"] = toSatoshi(parseFloat($poloJSON[pair.replace("polo_", "").toUpperCase()]["last"]), digits);
          break;
        case 2:
          $status[pair]["value"] = parseFloat($poloJSON[pair.replace("polo_", "").toUpperCase()]["last"]).toExponential();
          break;
      }
      /*
      if ($toExponential) {
        $status[pair]["value"] = parseFloat($poloJSON[pair.replace("polo_", "").toUpperCase()]["last"]).toExponential();
      } else {
        $status[pair]["value"] = $poloJSON[pair.replace("polo_", "").toUpperCase()]["last"];
      }
      */
    }
  }
}

function bt_update(pair, digits) {
  try {
    ajax({
      url: 'https://bittrex.com/api/v1.1/public/getticker?market=' + pair.replace("bt_", "").replace("_", "-").toUpperCase(),
      type: 'json',
      async: false
    }, function (data) {
      if (pair.match(/^bt_usdt/)) {
        $status[pair]["value"] = floatFormat(parseFloat(data["result"]["Last"]), digits);
      } else {
        switch ($currentDecimalMode) {
          case 0:
            $status[pair]["value"] = data["result"]["Last"];
            break;
          case 1:
            $status[pair]["value"] = toSatoshi(parseFloat(data["result"]["Last"]), digits);
            break;
          case 2:
            $status[pair]["value"] = parseFloat(data["result"]["Last"]).toExponential();
            break;
        }
        /*
        if ($toExponential) {
          $status[pair]["value"] = parseFloat(data["result"]["Last"]).toExponential();
        } else {
          $status[pair]["value"] = data["result"]["Last"];
        }
        */
      }
    });
  } catch (e) {
    console.log(e);
    simply.body(e);
  }
}

function bfx_update(pair, digits) {
  try {
    ajax({
      url: 'https://api.bitfinex.com/v1/pubticker/' + pair.replace("bfx_", "").split("_").reverse().join(""),
      type:'json',
      async: false
      }, function(data) {
      if (pair.match(/usd/)) {
        $status[pair]["value"] = floatFormat(data["last_price"], digits);
      } else {
        switch ($currentDecimalMode) {
          case 0:
            $status[pair]["value"] = data["last_price"];
            break;
          case 1:
            $status[pair]["value"] = toSatoshi(parseFloat(data["last_price"]), digits);
            break;
          case 2:
            $status[pair]["value"] = parseFloat(data["last_price"]).toExponential();
            break;
        }
        /*
        if ($toExponential) {
          $status[pair]["value"] = parseFloat(data["last_price"]).toExponential();
        } else {
          $status[pair]["value"] = data["last_price"];
        }
        */
      }
    });
  } catch (e) {
    console.log(e);
    simply.body(e);
  }
}

function cmc_update(pair, digits) {
  try {
    ajax({
      url: 'https://api.coinmarketcap.com/v1/ticker/' + pair.replace(/cmc_(usd|btc|jpy)_/, "") + '/?convert=JPY',
      type:'json',
      async: false
      }, function(data) {
      var baseCurrency = pair.replace(/cmc_(usd|btc|jpy)_.+/, "$1");
      if (data.length == 1) {
        data = data[0];
        if (baseCurrency == "usd") {
          $status[pair]["value"] = floatFormat(data["price_usd"], digits);
        } else if (baseCurrency == "jpy") {
          $status[pair]["value"] = floatFormat(data["price_jpy"], digits);
        } else {
          switch ($currentDecimalMode) {
            case 0:
              $status[pair]["value"] = data["price_btc"];
              break;
            case 1:
              $status[pair]["value"] = toSatoshi(parseFloat(data["price_btc"]), digits);
              break;
            case 2:
              $status[pair]["value"] = parseFloat(data["price_btc"]).toExponential();
              break;
          }
          /*
          if ($toExponential) {
            $status[pair]["value"] = parseFloat(data["price_btc"]).toExponential();
          } else {
            $status[pair]["value"] = data["price_btc"];
          }
          */
        }
      }
    });
  } catch (e) {
    console.log(e);
    simply.body(e);
  }
}

function bb_update(pair, digits) {
  try {
    ajax({
      url: 'https://public.bitbank.cc/' + pair.replace(/bb_/, "").split("_").reverse().join("_") + '/ticker',
      type:'json',
      async:false
      }, function(data) {
        if (pair.match(/^bb_jpy/)) {
          $status[pair]["value"] = floatFormat(data["data"]["last"], digits);
        } else {
          switch ($currentDecimalMode) {
            case 0:
              $status[pair]["value"] = data["data"]["last"];
              break;
            case 1:
              $status[pair]["value"] = toSatoshi(parseFloat(data["data"]["last"]), digits);
              break;
            case 2:
              $status[pair]["value"] = parseFloat(data["data"]["last"]).toExponential();
              break;
          }
          /*
          if ($toExponential) {
            $status[pair]["value"] = parseFloat(data["data"]["last"]).toExponential();
          } else {
            $status[pair]["value"] = data["data"]["last"];
          }
          */
        }
    });
  } catch (e) {
    console.log(e);
    simply.body(e);
  }
}

function ok_update(pair, digits) {
  try {
    ajax({
      url: 'https://www.okcoin.com/api/v1/ticker.do?symbol=' + pair.replace(/ok_/, "").split("_").reverse().join("_"),
      type:'json',
      async:false
      }, function(data) {
        $status[pair]["value"] = floatFormat(data["ticker"]["last"], digits);
    });
  } catch (e) {
    console.log(e);
    simply.body(e);
  }
}

function updateSubtitle() {
  $subtitle_fmt = $modes[$currentMode]["subtitle"];
  for (var pair in $status) {
    $subtitle_fmt = $subtitle_fmt.replace("$" + pair, $status[pair]["value"]);
  }
  simply.subtitle($subtitle_fmt);
}

function updateBody() {
  $body_fmt = $modes[$currentMode]["body"];
  for (var pair in $status) {
    $body_fmt = $body_fmt.replace("$" + pair, $status[pair]["value"]);
  }
  simply.body($body_fmt);
}

function refresh() {
  simply.title(timeText());
  if ($modes[$currentMode]["subtitle"].match("polo_") || $modes[$currentMode]["body"].match("polo_")) {
    updatePoloJSON();
  }
  for (var pair in $status) {
    if ($modes[$currentMode]["subtitle"].match(pair) || $modes[$currentMode]["body"].match(pair)) {
      if (pair.match(/^cc_/)) {
        cc_update(pair, $status[pair]["digits"]);
      } else if (pair.match(/^zf_/)) {
        zf_update(pair, $status[pair]["digits"]);
  	  } else if (pair.match(/^bf_/)) {
    	  bf_update(pair, $status[pair]["digits"]);
      } else if (pair.match(/^polo_/)) {
        polo_update(pair, $status[pair]["digits"]);
      } else if (pair.match(/^bt_/)) {
        bt_update(pair, $status[pair]["digits"]);
      } else if (pair.match(/^bfx_/)) {
    	  bfx_update(pair, $status[pair]["digits"]);
    	} else if (pair.match(/^cmc_/)) {
      	cmc_update(pair, $status[pair]["digits"]);
    	} else if (pair.match(/^bb_/)) {
      	bb_update(pair, $status[pair]["digits"]);
    	} else if (pair.match(/^ok_/)) {
      	ok_update(pair, $status[pair]["digits"]);
      }
    }
  }
  updateSubtitle();
  updateBody();
}

// イベントハンドラ

simply.on('singleClick', function (e) {
  simply.vibe();
  if (e.button == 'up') {
    $currentMode = $currentMode - 1;
    if ($currentMode == -1) {
      $currentMode = $modes.length - 1;
    }
  } else if (e.button == 'down') {
    $currentMode = $currentMode + 1;
    if ($currentMode == $modes.length) {
      $currentMode = 0;
    }
  } else if (e.button == 'select') {
    $currentDecimalMode = $currentDecimalMode + 1;
    if ($currentDecimalMode > 2) {
      $currentDecimalMode = 0;
    }
  }
  refresh();
});

simply.on('accelTap', function (e) {
  simply.vibe();
  refresh();
});

// エントリポイント

simply.begin = function () {
  try {
    simply.fullscreen(true);
    refresh();
    setInterval(refresh, $interval * 1000);
  } catch (e) {
    console.log(e);
    simply.body(e);
  }
};
