package by.isysoi.model.client;

import io.netty.buffer.ByteBuf;
import io.netty.buffer.Unpooled;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.util.CharsetUtil;
import io.netty.util.ReferenceCountUtil;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.swing.*;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Vector;

@ChannelHandler.Sharable
public class ClientHandler extends ChannelInboundHandlerAdapter {

    private static final Logger logger = LogManager.getLogger();

    private String name;
    private ClientInterface client;

    ClientHandler(ClientInterface client) {
        this.client = client;
    }

    @Override
    public void channelActive(ChannelHandlerContext ctx) throws Exception {
        super.channelActive(ctx);
        client.getImageList().addListSelectionListener(event -> {
            if (!event.getValueIsAdjusting()) {
                String anotherClient = client.getAnotherClientName();
                JList source = (JList) event.getSource();
                if (anotherClient != null) {
                    source.getSelectedValue();
                    String image = source.getSelectedValue().toString();
                    ctx.writeAndFlush(Unpooled.copiedBuffer(anotherClient + " image: " + image, CharsetUtil.UTF_8));
                    logger.info("Send image");
                }
            }

        });

        client.getFrame().addWindowListener(new java.awt.event.WindowAdapter() {
            @Override
            public void windowClosing(java.awt.event.WindowEvent windowEvent) {
                if (JOptionPane.showConfirmDialog(client.getFrame(),
                        "Are you sure you want to close this window?", "Close Window?",
                        JOptionPane.YES_NO_OPTION,
                        JOptionPane.QUESTION_MESSAGE) == JOptionPane.YES_OPTION) {
                    logger.info("Close client");
                    ctx.writeAndFlush(Unpooled.copiedBuffer("EXIT " + name, CharsetUtil.UTF_8));
                    ctx.channel().close();
                    System.exit(0);
                }
            }
        });
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext channelHandlerContext, Throwable cause) {
        cause.printStackTrace();
        channelHandlerContext.close();
    }

    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) {
        String input = ((ByteBuf) msg).toString(CharsetUtil.UTF_8).trim();

        if (input.startsWith("SUBMIT_NAME")) {
            String name = null;
            while (name == null) {
                name = client.getName();
            }

            this.name = name;
            ctx.writeAndFlush(Unpooled.copiedBuffer("NAME " + name, CharsetUtil.UTF_8));
            logger.info("Try register name:" + name);
        } else if (input.startsWith("NAME_ACCEPTED")) {
            client.getImageList().setVisible(true);
            client.getFrame().setTitle(client.getFrame().getTitle() + ": " + name);
            logger.info("Show client images:" + name);
        } else if (input.startsWith("FAIL_USER")) {
            JOptionPane.showMessageDialog(
                    client.getFrame(),
                    "User not found",
                    "Fail",
                    JOptionPane.PLAIN_MESSAGE);
            logger.info("User not found server answer");
        } else if (input.startsWith("IMAGE")) {
            JOptionPane.showMessageDialog(
                    client.getFrame(),
                    "You got image",
                    "New image",
                    JOptionPane.PLAIN_MESSAGE);
            String imageURL = input.substring(5);
            try {
                client.getMyImages().add(new ImageIcon(new URL(imageURL)));
            } catch (MalformedURLException e) {
                e.printStackTrace();
            }
            client.getImageList().setListData(new Vector<>(client.getMyImages()));
            logger.info("Accept new image");
        }
        ReferenceCountUtil.release(msg);
    }
}