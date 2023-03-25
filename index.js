const express = require('express');
const app = express();

app.set('view engine', 'ejs');
app.use(express.static("views"))
app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
    res.render("index.ejs")
})

app.post("/", (req, res) => {
    const buttonValue = req.body.value;
    console.log(buttonValue)
    res.send( buttonValue);
});

app.get('/on', (req, res) => {
    res.send("1")
})
app.get('/off', (req, res) => {
    res.send("0")
})

app.listen(4000)