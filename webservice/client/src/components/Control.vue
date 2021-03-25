<template>
	<div id="app-messenger" class="">
		<section class="section hero is-danger is-fullheight">
			<div class="hero-body">
				<div class="container has-text-centered">
					<h1 class="title is-large has-text-weight-semibold">{{ message }}</h1>
					<div style="background-color: black; opacity: 0.1; border-radius: 20px; position: absolute; top: -30vh; left: 10vw; right: 10vw; height: 70vh; overflow: hidden">
						<div ref="nipple" class="nipple" id="nipple"></div>
					</div>
				</div>
			</div>
		</section>
	</div>
</template>

<script>
import nipplejs from 'nipplejs';
export default {
	name: 'Control',
	data: () => ({
		manager: null,
		message: "	"
	}),
	components: {
	},
	methods: {
		onUp: function(){
			this.$emit( "input", {dir: 'forward'});
			this.$data.message = "⬆️"
		},
		onRight: function(){
			this.$data.message = "➡️"
			this.$emit( "input", {dir: 'right'});
		},
		onDown: function(){
			this.$emit( "input", {dir: 'backward'});
			this.$data.message = "⬇️"
		},
		onLeft: function(){
			this.$emit( "input", {dir: 'left'});
			this.$data.message = "⬅️"
		},
		onEnd: function(){
			this.$emit( "input", {dir: 'end'});
			this.$data.message = "	"
		},
	},
	mounted() {
		let opt = nipplejs.create({
			zone: document.getElementById("nipple"),
			mode: 'dynamic',
			// position: {left: '50%', top: '50%'},
			// color: 'red'
		});

		this.$data.manager = nipplejs.create(opt);
    this.$data.manager.options.zone = this.$refs.nipple

		// Bind events
		//this.$data.manager.on("dir:up", ()=> this.onUp())
		//this.$data.manager.on("dir:right", ()=> this.onRight())
		//this.$data.manager.on("dir:down", ()=> this.onDown())
		//this.$data.manager.on("dir:left", ()=> this.onLeft())
		//this.$data.manager.on("end", ()=> this.onEnd())

		this.$data.manager.on('move', (e, data) => {
			let phi = 90 - data.angle.degree

			if (phi < -30 ) phi = -30
			if (phi > 30 ) phi = 30

			this.$emit( "input", {dir: phi});
		})
	}
}
</script>

<style>
#app-messenger {
	font-family: Avenir, Helvetica, Arial, sans-serif;
	-webkit-font-smoothing: antialiased;
	-moz-osx-font-smoothing: grayscale;
	text-align: center;
	color: #2c3e50;
}

#twemoji-textarea-outer{
	border-radius: 20px;
}

.emoji-popover-inner{
	height: 300px;
}
</style>
