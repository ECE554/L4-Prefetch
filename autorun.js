const { execFile } = require('child_process');
var fs = require('fs');


var run_data = {
    nextline: {
        config: 'cache-lru-nextline.cfg'
    },
    stride: {
        config: 'cache-lru-stride.cfg'
    },
    open: {
        config: 'cache-lru-open.cfg'
    },
    benchmarks: [
        'compress.eio',
        'gcc.eio',
        'go.eio'
    ],
    paths: {
        config: 'cache-config/',
        benchmark: '/cad2/ece552f/benchmarks/'
    }
}

var miss_rate_regex = /(?:\ndl1.miss_rate[ ]*)[+-]?([0-9]*[.]*[0-9]*)?/i;
var filename_regex = /(?:sim: loading EIO file: \/cad2\/ece552f\/benchmarks\/)[+-]?([a-z]*.[a-z]*)?/i;
var type;
var bm = -1;

process.argv.forEach(function (val, index, array) {
    if (index == 2) type = val;
    if (val == '-b') {
        bm = array[index + 1];
    }
});

var config = null;
if (type == 'nextline') {
    config = run_data.nextline.config;
}
else if (type == 'stride') {
    config = run_data.stride.config;
}
else if (type == 'open') {
    config = run_data.open.config;
}

if (config == null) {
    console.log("No config set (nextline, stridr, open)");
    process.exit();
}

if (bm == -1) {
    var count = 0;
    for (var i = 0; i < run_data.benchmarks.length; i++) {
        execFile('./sim-cache', [
            '-redir:sim',
            run_data.benchmarks[i] + '.rout',
            '-config',
            run_data.paths.config + config,
            run_data.paths.benchmark + run_data.benchmarks[i]
        ], function(err, data) {
            if (err) {
                console.log(err);
            }
            count++;
            
            if (count == run_data.benchmarks.length) {
                var mrts = [];

                for (var j = 0; j < run_data.benchmarks.length; j++) {
                    fs.readFile(run_data.benchmarks[j] + '.rout', "utf8", function(err, data) {
                        if (err) {
                            console.log(err);
                        } else {
                            var mr = data.match(miss_rate_regex)[1];
                            var file = data.match(filename_regex)[1];
                            mrts.push(mr);
                            console.log(file + ' :\t' + mr);

                            if (mrts.length == run_data.benchmarks.length) {
                                var sum = 0;
                                mrts.forEach(function(v) {
                                    sum += parseFloat(v);
                                });
                                console.log("AVG :\t\t" + sum / run_data.benchmarks.length);
                            }
                        }
                    });
                }
            }
        });
    }
} else {
    execFile('./sim-cache', [
        '-redir:sim',
        run_data.benchmarks[bm] + '.rout',
        '-config',
        run_data.paths.config + config,
        run_data.paths.benchmark + run_data.benchmarks[bm]
    ], function(err, data) {
        if (err) {
            console.log(err);
        }

        fs.readFile(run_data.benchmarks[bm] + '.rout', "utf8", function(err, data) {
            console.log(data);
        });
    });
}
