// app.js
// Entry point of the web server

// Require necessary modules
var express = require('express');
var path = require('path');
var app = express();

// Use EJS templating
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// Setup static files path
app.use(express.static(path.join(__dirname, 'public')));

// Configure routes
app.get('/', function(req, res) {
    res.render('index');
});

// Start server listening on the specified port
app.listen(3000, function() {
    console.log('Node server is now listening on port 3000.');
});
