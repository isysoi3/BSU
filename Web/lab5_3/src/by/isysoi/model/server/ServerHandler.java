package by.isysoi.model.server;

import io.netty.buffer.ByteBuf;
import io.netty.buffer.Unpooled;
import io.netty.channel.Channel;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.util.CharsetUtil;
import io.netty.util.ReferenceCountUtil;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.HashMap;
import java.util.Map;

/**
 * class of server handler that handling connections
 *
 * @author Ilya Sysoi
 * @version 1.0
 */
@ChannelHandler.Sharable
public class ServerHandler extends ChannelInboundHandlerAdapter {

    private static final Logger logger = LogManager.getLogger();

    private static Map<String, Channel> clients = new HashMap<>();

    @Override
    public void channelRegistered(ChannelHandlerContext ctx) throws ServerException {
        try {
            super.channelRegistered(ctx);
        } catch (Exception e) {
            throw new ServerException("channelRegistered", e);
        }
        ctx.writeAndFlush(Unpooled.copiedBuffer("SUBMIT_NAME", CharsetUtil.UTF_8));
    }

    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) {

        String input = ((ByteBuf) msg).toString(CharsetUtil.UTF_8).trim();

        if (input.startsWith("NAME")) {
            String[] rez = input.split("NAME ");
            if (rez.length < 2) {
                ctx.writeAndFlush(Unpooled.copiedBuffer("SUBMIT_NAME", CharsetUtil.UTF_8));
            } else {
                String name = rez[1];
                if (clients.containsKey(name)) {
                    logger.info("Client with name ( " + name + " ) is already connected");
                    ctx.writeAndFlush(Unpooled.copiedBuffer("SUBMIT_NAME", CharsetUtil.UTF_8));
                } else {
                    logger.info("Client with name ( " + name + " ) is connected!");
                    clients.put(name, ctx.channel());
                    ctx.writeAndFlush(Unpooled.copiedBuffer("NAME_ACCEPTED", CharsetUtil.UTF_8));
                }
            }
        } else if (input.startsWith("EXIT")) {
            String[] rez = input.split("EXIT ");
            String name = rez[1];

            clients.remove(name);
            ctx.channel().close();
            logger.info("Client ( " + name + " ) removed");
        } else {
            String[] rez = input.split(" image: ");
            if (clients.containsKey(rez[0])) {
                clients.get(rez[0]).writeAndFlush(Unpooled.copiedBuffer("IMAGE " + rez[1], CharsetUtil.UTF_8));
                logger.info("Send image to ( " + rez[0] + " )");
            } else {
                ctx.writeAndFlush(Unpooled.copiedBuffer("FAIL_USER", CharsetUtil.UTF_8));
                logger.info("Client with name ( " + rez[0] + " ) doesn`t exists!");
            }

        }
        ReferenceCountUtil.release(msg);
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws ServerException {
        ctx.close();
        throw new ServerException("exceptionCaught", cause);
    }
}
