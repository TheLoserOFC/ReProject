const { json } = require("express");

const mongoose = require("mongoose");
const user_model = require("../../mongo_models/user_model");
const UnixConverter = require("../../Utils/Convertions/UnixConverter");




const TokenGenerete = require("../../Utils/Gerations/Token");



var ResponseType = {
    OK: 0,
    INVALID_USER: 1,
    INVALID_PASSOWORD: 2,
    INVALID_HWID: 3,
    INVALID_SUB: 4,
    BANNED: 5
}


const user = mongoose.model('users', user_model);

function ResponseStatus(Response, message, realname, expire) {

    var preset = {
        USER: {
            username: realname,
            expire: Response === 0 ? UnixConverter(expire) : "",
        },
        STATUS: {
            status: Response,
            token: TokenGenerete(30)
        }
    }

    return preset;
}

module.exports = function APILoader(req, res)  {

    var _user = "the_gz";
    

    user.findOne({"username": _user}).then(result => {
        res.send(ResponseStatus(ResponseType.OK, "", result.realname, result.expire));
    }).catch(err => console.log("Erro ao Puxar informação de " + _user + " " + err));

    

};