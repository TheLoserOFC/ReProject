const config = require('./Utils/configs.json')
const { Client, Intents, MessageEmbed } = require('discord.js');
const help = require('./commands/help');
const clear = require('./commands/clear');
const info = require('./commands/info');
const myIntents = new Intents(Intents.ALL);
const app = new Client({ ws: { intents: myIntents } });

app.on('message', async message => {
    if (message.author.bot) return;
    if (message.channel.type == "dm") return;


    var prefix = config.prefix;

    //Sistema de Mencionar o Bot Mostra o Prefix
    if (message.mentions.members.first() == message.guild.members.cache.get('831586063902048297'))
        return message.channel.send(`Meu Prefixo neste server é: ${prefix}`);

    //AntiLinks(message);
    //AntiPalavrao(message);




    //agumentos e comandos
    let args = message.content.slice(prefix.length).trim().split(/ +/g);
    let comando = args.shift().toLowerCase();
    //let argumentos = args.join(" ");

    if (!message.content.startsWith(prefix))
        return;

    if (message.channel.id != "827985133822935057" && message.channel.id != "813631353995919380" && !message.member.hasPermission("ADMINISTRATOR")) {
        app.guilds.cache.get("747866056948711514").channels.cache.get("827985133822935057").send(`${message.author} Comandos São Realizados Aqui!`)
        return message.delete();
    }
        //Hook Comandos!
    help(message, comando, prefix);
    clear(message, comando, args);
    info(message, comando, args);

});


app.login(config.token);