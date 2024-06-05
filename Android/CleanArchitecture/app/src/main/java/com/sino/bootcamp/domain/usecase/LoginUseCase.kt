package com.sino.bootcamp.domain.usecase

import com.sino.bootcamp.data.repository.LoginRepository
import com.sino.bootcamp.data.repository.impl.DefaultLoginRepository


//can manager many repository
class LoginUseCase(
    private val loginRepository: LoginRepository = DefaultLoginRepository(),
    ) {
    operator fun invoke(phone:String, code :String): String {
       return loginRepository.login(phone,code);
    }
}


