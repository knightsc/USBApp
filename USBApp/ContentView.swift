//
//  ContentView.swift
//  USBApp
//
//  Created by Scott Knight on 6/13/19.
//  Copyright © 2019 Scott Knight. All rights reserved.
//

import SwiftUI
import SystemExtensions

struct ContentView : View {
    var body: some View {
        VStack {
            Text("USBApp")
            HStack {
                Button(action: ExtensionManager.shared.activate) {
                    Text("Activate")
                }
                Button(action: ExtensionManager.shared.deactivate) {
                    Text("Deactivate")
                }
            }
        }
        .frame(maxWidth: .infinity, maxHeight: .infinity)
    }
}


#if DEBUG
struct ContentView_Previews : PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
#endif
