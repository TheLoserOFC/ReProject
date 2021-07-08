const mongoose = require('mongoose');

const user_model = new mongoose.Schema({
    realname: String, // Nome Real sensivel a Maiusculo e minusculo
    username: String, // TD minusculo
    email: String,
    password: String,
    discord: String,
    register: Number,
    expire: Number,
    newreset: Number,
    hwid: Number,
    ban: Boolean,
    admin: Boolean
});

module.exports = user_model;