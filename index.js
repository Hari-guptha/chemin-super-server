const express = require('express');
const app = express();

app.get('/api', (req, res) => {
    res.send("holly cow")
})

app.post('/home', (req, res) => {
    res.send("we are good")
})


app.listen(4000)