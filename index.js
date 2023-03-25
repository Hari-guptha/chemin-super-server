const express = require('express');
const app = express();

var buttonValue1 = 0
var buttonValue2 = 0
var buttonValue3 = 0


app.set('view engine', 'ejs');
app.use(express.static("views"))
app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
    res.render("index.ejs")

})

app.post("/post1", (req, res) => {
    buttonValue1 = req.body.value;
});
app.post("/post2", (req, res) => {
    buttonValue2 = req.body.value;
});
app.post("/post3", (req, res) => {
    buttonValue3 = req.body.value;
});

app.get("/fun",(req,res)=>{
    res.send(`${buttonValue1}`);
    res.send(`${buttonValue2}`);
    res.send(`${buttonValue3}`);
})


app.listen(4000)