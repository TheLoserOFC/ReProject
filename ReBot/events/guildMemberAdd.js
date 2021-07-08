
function AutoRole(member, autorole, role) {

	if(!autorole)
	   return;
	if(!role) 
	   return;
	
	member.roles.add(role).catch(console.error);
}
function Welcome(member, welcome, canal, msg) {
	if(!welcome)
	   return;

	if(!canal)
	   return;

	if(!msg)
	   return;

	   var a = msg.replace('{@user}', member.user).replace('{guild}', member.guild.name)
	   
	   canal.send(JSON.parse(a))
}

module.exports = async function guildMemberAdd(member) {
	
	let guild = member.guild;

	
	const GUILDA = mongoose.model('Exodo_Bot', guild_model)
	GUILDA.findOne({Guild: `${guild.id}`}).then(result => {
		var autorole = result.AutoRole;
		var welcome = result.Entrada;

		
		var msg = result.msg_welcome;

		var canal = guild.channels.cache.find(c => c.id === `${result.Canal_entrada}`);
		var role = guild.roles.cache.find(r => r.id === result.Role_entrada);
		
		

		Welcome(member, welcome, canal, msg);
		AutoRole(member, autorole, role);
	}).catch(e => {
		console.log(e)
	});	
}