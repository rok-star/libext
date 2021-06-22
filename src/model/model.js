const { readFileSync } = require('fs');
const { resolve } = require('path');

const makeClass = () => {
    return [ 'hpp', 'cpp' ]
}

const modelPath = resolve(process.argv[2]);
const modelData = JSON.parse(readFileSync(modelPath).toString());

