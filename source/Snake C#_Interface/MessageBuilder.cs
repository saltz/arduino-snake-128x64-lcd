using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace oit_toets3_snake
{
    public class MessageBuilder
    {
        /// <summary>
        /// Message from which more characters are to be expected from the feed.
        /// </summary>
        private string partlyMessage;

        /// <summary>
        /// Buffer to store messages found in the feed.
        /// Needed because its possible that multiple messages are parsed from the data input
        /// </summary>
        private Queue<string> messages;

        /// <summary>
        /// Marker that marks the start of a message.
        /// </summary>
        public char MessageBeginMarker { get; private set; }

        /// <summary>
        /// Marker that marks the mark the end of a message.
        /// </summary>
        public char MessageEndMarker { get; private set; }

        /// <summary>
        /// The number of available messages which can be retrieved using GetNextMessage()
        /// </summary>
        /// <returns></returns>
        public int MessageCount
        {
            get
            {
                return messages.Count;
            }
        }

        /// <summary>
        /// Create a MessageBuilder instance.
        /// </summary>
        /// <param name="messageBeginMarker">
        /// Marker that is used to find the start of a message 
        /// when trying to find messages in the buffered data.
        /// </param>
        /// <param name="messageEndMarker">
        /// Marker that is used to find the end of a message 
        /// when trying to find messages in the buffered data.
        /// </param>
        public MessageBuilder(char messageBeginMarker, char messageEndMarker)
        {
            MessageBeginMarker = messageBeginMarker;
            MessageEndMarker = messageEndMarker;
            messages = new Queue<string>();
            partlyMessage = null;
        }

        /// <summary>
        /// Feeds data containing (possible) messages to the MessageBuilder.
        /// After using Add, use GetMessage() to retrieve messages contained in the data.
        /// 
        /// Its possible that an incomplete message is contained in the data.
        /// </summary>
        /// <param name="data">
        /// data from the feed containing possible messages.
        /// </param>
        public void Add(string data)
        {
            if (data == null)
            {
                throw new ArgumentNullException("data");
            }

            string message;
            bool messageStarted;
            if (partlyMessage != null)
            {
                message = partlyMessage;
                messageStarted = true;
                partlyMessage = null;
            }
            else
            {
                message = "";
                messageStarted = false;
            }

            foreach (char character in data)
            {
                if (messageStarted)
                {
                    if (character != MessageEndMarker)
                    {
                        message += character;
                    }
                    else
                    {
                        messages.Enqueue(message);
                        message = "";
                        messageStarted = false;
                    }
                }
                else
                {
                    if (character == MessageBeginMarker)
                    {
                        messageStarted = true;
                    }
                }
            }

            if (messageStarted)
            {
                partlyMessage = message;
            }
        }

        /// <summary>
        /// Gets the next message that was present in the MessageBuilder.
        /// Use Add() to add data to the MessageBuilder from which messages should be extracted.
        /// 
        /// It's possible that multiple messages are present in the MessageBuilder. 
        /// So call GetMessage() until it returns null after using Add().
        /// </summary>
        /// <returns>
        /// The next message, or null if no message was present in the builder.
        /// </returns>
        public string GetNextMessage()
        {
            if (messages.Count > 0)
            {
                return messages.Dequeue();
            }
            return null;
        }

        /// <summary>
        /// Clear all buffered messages and message data
        /// </summary>
        public void Clear()
        {
            messages.Clear();
            partlyMessage = null;
        }
    }
}
