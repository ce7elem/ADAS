<template>
	<div id="app-fridge" class="is-fullheight">
		<section class="section hero is-success is-fullheight">
			<div class="hero-body">
				<div class="container">
					<ul v-for="(item, i) in todos" :key="i">
						<li class="list-item">
							<div class="is-flex box" style="align-items: center">
							<span class="is-pulled-left">{{item.text}}</span>
							<div style="flex: 1"></div>
							<button class="button is-text is-pulled-right is-big has-text-black" @click="removeTodo(i)">
								<span class="icon">
									<i class="fas fa-check"></i>
								</span>
							</button>
							</div>
						</li>
					</ul>
					<p v-if="!todos.length" class="has-text-centered">Nothing here !</p>
				</div>
			</div>
		</section>

	</div>
</template>

<script>

export default {
	name: 'Fridge',
	data: () => ({
		todos: [
			{ text: "oui" },
			{ text: "Non" }
		]
	}),

	methods: {
		removeTodo(id){
			this.$socket.emit("removeTask", {"id": id})
		}
	},
}
</script>

<style>
#app-fridge {
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
