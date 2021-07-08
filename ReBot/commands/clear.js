const { Client, Intents, MessageEmbed } = require('discord.js');
const myIntents = new Intents(Intents.ALL);
const client = new Client({ ws: { intents: myIntents } });


module.exports = async (message, commando, args) => {
    if (commando != "clear" && commando != "limpar") return;

    message.delete();

    if (!message.member.hasPermission("MANAGE_MESSAGES")) {
        var UMSG = await message.channel.send(`${message.author} Você não Possui Permissão Para Usar este Comando!`);
        var inter = setInterval(() => { UMSG.delete(); clearInterval(inter) }, 5000);
        return;
    }

    if (!args[0]) {
        var msg = await message.channel.send(`Você não Especificou a quantidade de Mensagens para Deletar! ${message.author}`)
        var inter = setInterval(() => { msg.delete(); clearInterval(inter) }, 4000);
        return;
    }

    if (!parseInt(args[0])) {
        var msg = await message.channel.send(`${message.author} Você Precisa informar a quantidade Em Numeros!`);
        var inter = setInterval(() => { msg.delete(); clearInterval(inter) }, 4000);
        return;
    }

    if (parseInt(args[0]) > 100) {
        var msg = await message.channel.send("Você não pode deletar mais de 100 Mensagens!");
        var inter = setInterval(() => { msg.delete(); clearInterval(inter) }, 4000);
        return;
    }

    if (parseInt(args[0]) <= 1) {
        var msg = await message.channel.send(`${message.author} Você não pode deletar menos de 2 Mensagens!`);
        var inter = setInterval(() => { msg.delete(); clearInterval(inter) }, 4000);
        return;
    }

    message.channel.bulkDelete(parseInt(args[0])).catch(err => {
        message.channel.send(`${message.author} Há Mensagens! que não posso deletar porque já tem mais de 2 semana!`)

        var inter = setInterval(() => { message.channel.bulkDelete(1); clearInterval(inter) }, 4000);
        return;
    });

    var msg = await message.channel.send(`Pronto! ${message.author}, Deletei às Mensagens!`)

    var inter = setInterval(() => { msg.delete(); clearInterval(inter) }, 4000);

}