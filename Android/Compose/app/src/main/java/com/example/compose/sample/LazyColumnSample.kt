package com.example.compose.sample


import android.util.Log
import androidx.compose.foundation.ExperimentalFoundationApi
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.foundation.lazy.grid.items
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.lazy.rememberLazyListState
import androidx.compose.material3.Divider
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.DisposableEffect
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp


@OptIn(ExperimentalFoundationApi::class)
@Composable
fun LazyColumnSample1() {
    val items = listOf(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20)
    var height: Dp
    with(LocalDensity.current) {
        height = 300.toDp()
    }

    val state = rememberLazyListState()
    val scope = rememberCoroutineScope()
    LazyColumn(state = state) {
        stickyHeader {
            Text(
                "Header", modifier = Modifier
                    .fillMaxWidth()
                    .background(Color.White)
                    .padding(vertical = 10.dp)
                    .clickable {
                      //  scope.launch { state.animateScrollToItem(2) }
                    },fontSize = 22.sp
            )
        }
        items(items) {
            Text(
                text = "Column Item :$it", modifier = Modifier
                    .height(height),
                fontSize = 20.sp
            )
            Divider()
            DisposableEffect(Unit) {
                Log.d("LazyColumn", "effect:$it")
                onDispose {
                    Log.e("LazyColumn", "onDispose:$it")
                }
            }
        }
    }
}

@Composable
fun LazyVerticalGridSample() {
    val datas = listOf(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
    LazyVerticalGrid(columns = GridCells.Fixed(2)) {
        items(datas) {
            Text("Grid Item $it",
                fontSize = 24.sp)
        }
    }
}

@Preview
@Composable
fun LazyColumnSamplePreview() {
    LazyColumnSample1()
}
