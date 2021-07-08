const { Client, Intents, MessageEmbed } = require('discord.js');


module.exports = function help(message, comando, prefix) {
    if(comando != "ajuda" && comando != "help") return;
    
    return message.channel.send(
        new MessageEmbed()
        .setColor("#1e058d")
        .addFields({ name: "Obter informação de um User do Cheat", value: `${prefix}info`, inline: false })
        .setFooter("control.gg")
    )
}