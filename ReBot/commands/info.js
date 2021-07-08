
const { Client, Intents, MessageEmbed } = require('discord.js');

const mongoose = require('mongoose');
const user_model = require('../Utils/mongodb/user_model');
const timeConverter = require('../Utils/TimeFormat');

mongoose.connect("mongodb://localhost:27017/control_db", { useNewUrlParser: true, useUnifiedTopology: true }).then(() => console.log('mongo OK')).catch(() => console.log('Erro ao conectar ao Mongo'))

module.exports = async (message, comando, args) => {


    

    if(comando != "info" && comando != "informação") return;


    let user = mongoose.model('users', user_model);

    if(!args[0]) {
        return message.channel.send('Please Please write the name of the user!')
    }

    user.findOne({'username': args[0]}).then(result => {


        if(!result) {
            return message.channel.send('This user was not found!')
        }

        message.channel.send(
            new MessageEmbed()
            .setTitle("Contro Infos")
            .setColor("#1e058d")
            //.setDescription(`Estou em desenvolvimento ainda :( mas brevemente estarei disponivel :)`)
            .setDescription(`Username: ${result.realname} \n Status: ${result.expire > new Date().getTime() / 1000 ? 'Active' : 'Inactive'} \n Expire: ${result.expire > new Date().getTime() / 1000 ? timeConverter(result.expire) : 'Freezed'}`)
        )
    }).catch(() => console.log('Erro :('))

    

}