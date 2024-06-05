package com.sino.bootcamp.data.repository.impl

import com.sino.bootcamp.data.repository.LoginRepository



class DefaultLoginRepository(): LoginRepository {
    override  fun login(phone: String, code: String): String = "user-token:11111111"
}