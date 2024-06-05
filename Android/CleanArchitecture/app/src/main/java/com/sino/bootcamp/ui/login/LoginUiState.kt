package com.sino.bootcamp.ui.login

//UI State
sealed interface LoginUiState{
    data object Login : LoginUiState
    data object UnLogin : LoginUiState
}

