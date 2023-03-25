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

app.post("/post", (req, res) => {
    buttonValue = req.body.value;
});

app.get("/fun",(req,res)=>{
    res.send(`${buttonValue1}${buttonValue2}${buttonValue3}`);
})


app.listen(4000)