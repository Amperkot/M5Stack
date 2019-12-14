from microWebSrv import MicroWebSrv
from m5stack import lcd
import _thread
from callb import _acceptWebSocketCallback
import os


def _tryingmine(httpClient, httpResponse,routeArgs):
    lcd.clear(0x000000)
    lcd.font('hp.fon')
    lcd.setCursor(0,0)
    lcd.print(routeArgs['message'])
    httpResponse.WriteResponseOk( headers         = None,
                                 contentType     = "text/html",
                                 contentCharset = "UTF-8",
                                 content          = "OK" )

routeHandlers = [
 ("/my/<message>","GET",_tryingmine)
]

srv = MicroWebSrv(routeHandlers=routeHandlers)


srv.MaxWebSocketRecvLen     = 256
srv.WebSocketThreaded       = True
srv.WebSocketStackSize      = 4096
srv.AcceptWebSocketCallback = _acceptWebSocketCallback

srv.Start(threaded=True)
